#include <Arduino.h>
#include "globals.h"
#include <lvgl.h>
#include <ESP_Panel_Library.h>
#include <ESP_IOExpander_Library.h>
#include "ui/ui.h"
#include "espNowHelper.h"
#include <Preferences.h>
Preferences preferences; // NVS storage for user settings
unsigned long int previousuStatusCheckMillis = 0;
long uStatusCheckInterval = 33;

// Extend IO Pin define
#define TP_RST 1
#define LCD_BL 2
#define LCD_RST 3
#define SD_CS 4
#define USB_SEL 5

// I2C Pin define
#define I2C_MASTER_NUM 0
#define I2C_MASTER_SDA_IO 8
#define I2C_MASTER_SCL_IO 9

/**
/* To use the built-in examples and demos of LVGL uncomment the includes below respectively.
 * You also need to copy `lvgl/examples` to `lvgl/src/examples`. Similarly for the demos `lvgl/demos` to `lvgl/src/demos`.
 */
// #include <demos/lv_demos.h>
// #include <examples/lv_examples.h>

/* LVGL porting configurations */
#define LVGL_TICK_PERIOD_MS (2)
#define LVGL_TASK_MAX_DELAY_MS (500)
#define LVGL_TASK_MIN_DELAY_MS (1)
#define LVGL_TASK_STACK_SIZE (4 * 1024)
#define LVGL_TASK_PRIORITY (2)
#define LVGL_BUF_SIZE (ESP_PANEL_LCD_H_RES * 50)

ESP_Panel *panel = NULL;
SemaphoreHandle_t lvgl_mux = NULL; // LVGL mutex

#if ESP_PANEL_LCD_BUS_TYPE == ESP_PANEL_BUS_TYPE_RGB
/* Display flushing */
void lvgl_port_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
    panel->getLcd()->drawBitmap(area->x1, area->y1, area->x2 + 1, area->y2 + 1, color_p);
    lv_disp_flush_ready(disp);
}
#else
/* Display flushing */
void lvgl_port_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
    panel->getLcd()->drawBitmap(area->x1, area->y1, area->x2 + 1, area->y2 + 1, color_p);
}

bool notify_lvgl_flush_ready(void *user_ctx)
{
    lv_disp_drv_t *disp_driver = (lv_disp_drv_t *)user_ctx;
    lv_disp_flush_ready(disp_driver);
    return false;
}
#endif /* ESP_PANEL_LCD_BUS_TYPE */

#if ESP_PANEL_USE_LCD_TOUCH
/* Read the touchpad */
void lvgl_port_tp_read(lv_indev_drv_t *indev, lv_indev_data_t *data)
{
    panel->getLcdTouch()->readData();

    bool touched = panel->getLcdTouch()->getTouchState();
    if (!touched)
    {
        data->state = LV_INDEV_STATE_REL;
    }
    else
    {
        TouchPoint point = panel->getLcdTouch()->getPoint();

        data->state = LV_INDEV_STATE_PR;
        /*Set the coordinates*/
        data->point.x = point.x;
        data->point.y = point.y;

        // Serial0.printf("Touch point: x %d, y %d\n", point.x, point.y);
    }
}
#endif

void lvgl_port_lock(int timeout_ms)
{
    const TickType_t timeout_ticks = (timeout_ms < 0) ? portMAX_DELAY : pdMS_TO_TICKS(timeout_ms);
    xSemaphoreTakeRecursive(lvgl_mux, timeout_ticks);
}

void lvgl_port_unlock(void)
{
    xSemaphoreGiveRecursive(lvgl_mux);
}

void lvgl_port_task(void *arg)
{
    debugln("Starting LVGL task");

    uint32_t task_delay_ms = LVGL_TASK_MAX_DELAY_MS;
    while (1)
    {
        // Lock the mutex due to the LVGL APIs are not thread-safe
        lvgl_port_lock(-1);
        task_delay_ms = lv_timer_handler();
        // Release the mutex
        lvgl_port_unlock();
        if (task_delay_ms > LVGL_TASK_MAX_DELAY_MS)
        {
            task_delay_ms = LVGL_TASK_MAX_DELAY_MS;
        }
        else if (task_delay_ms < LVGL_TASK_MIN_DELAY_MS)
        {
            task_delay_ms = LVGL_TASK_MIN_DELAY_MS;
        }
        vTaskDelay(pdMS_TO_TICKS(task_delay_ms));
    }
}

void setup()
{
    Serial0.begin(115200); /* prepare for possible serial debug */

    String LVGL_Arduino = "Hello LVGL! ";
    LVGL_Arduino += String('V') + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch();

    debugln(LVGL_Arduino);
    debugln("I am ESP32_Display_Panel");

    panel = new ESP_Panel();

    /* Initialize LVGL core */
    lv_init();

    /* Initialize LVGL buffers */
    static lv_disp_draw_buf_t draw_buf;
    /* Using double buffers is more faster than single buffer */
    /* Using internal SRAM is more fast than PSRAM (Note: Memory allocated using `malloc` may be located in PSRAM.) */
    uint8_t *buf = (uint8_t *)heap_caps_calloc(1, LVGL_BUF_SIZE * sizeof(lv_color_t), MALLOC_CAP_INTERNAL);
    uint8_t *buf2 = (uint8_t *)heap_caps_calloc(1, LVGL_BUF_SIZE * sizeof(lv_color_t), MALLOC_CAP_INTERNAL);
    assert(buf);
    lv_disp_draw_buf_init(&draw_buf, buf, buf2, LVGL_BUF_SIZE);

    /* Initialize the display device */
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    /* Change the following line to your display resolution */
    disp_drv.hor_res = ESP_PANEL_LCD_H_RES;
    disp_drv.ver_res = ESP_PANEL_LCD_V_RES;
    disp_drv.flush_cb = lvgl_port_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);

#if ESP_PANEL_USE_LCD_TOUCH
    /* Initialize the input device */
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = lvgl_port_tp_read;
    lv_indev_drv_register(&indev_drv);
#endif
    /* Initialize bus and device of panel */
    panel->init();
#if ESP_PANEL_LCD_BUS_TYPE != ESP_PANEL_BUS_TYPE_RGB
    /* Register a function to notify LVGL when the panel is ready to flush */
    /* This is useful for refreshing the screen using DMA transfers */
    panel->getLcd()->setCallback(notify_lvgl_flush_ready, &disp_drv);
#endif

    /**
     * These development boards require the use of an IO expander to configure the screen,
     * so it needs to be initialized in advance and registered with the panel for use.
     *
     */
    debugln("Initialize IO expander");
    /* Initialize IO expander */
    // ESP_IOExpander *expander = new ESP_IOExpander_CH422G(I2C_MASTER_NUM, ESP_IO_EXPANDER_I2C_CH422G_ADDRESS_000, I2C_MASTER_SCL_IO, I2C_MASTER_SDA_IO);
    ESP_IOExpander *expander = new ESP_IOExpander_CH422G(I2C_MASTER_NUM, ESP_IO_EXPANDER_I2C_CH422G_ADDRESS_000);
    expander->init();
    expander->begin();
    expander->multiPinMode(TP_RST | LCD_BL | LCD_RST | SD_CS | USB_SEL, OUTPUT);
    expander->multiDigitalWrite(TP_RST | LCD_BL | LCD_RST | SD_CS, HIGH);

    // Turn off backlight
    // expander->digitalWrite(USB_SEL, LOW);
    expander->digitalWrite(USB_SEL, LOW);
    /* Add into panel */
    panel->addIOExpander(expander);

    /* Start panel */
    panel->begin();

    /* Create a task to run the LVGL task periodically */
    lvgl_mux = xSemaphoreCreateRecursiveMutex();
    xTaskCreate(lvgl_port_task, "lvgl", LVGL_TASK_STACK_SIZE, NULL, LVGL_TASK_PRIORITY, NULL);

    /* Lock the mutex due to the LVGL APIs are not thread-safe */
    lvgl_port_lock(-1);

    ui_init();

    /* Release the mutex */
    lvgl_port_unlock();
    espNowHelper::initialize();
    debugln("Setup done");
    // Start by reading saved preferences in from NVM
    preferences.begin("user_settings", false);
    int savedTheme = preferences.getInt("selectedTheme", 0);
    int screenTimeout = preferences.getInt("screenTimeout", 0);
    bool keepScreenOnWhileDriving = preferences.getBool("onWhileDriving", true);
    int gatewayMac1 = preferences.getInt("gatewayMac1", 00);
    int gatewayMac2 = preferences.getInt("gatewayMac2", 00);
    int gatewayMac3 = preferences.getInt("gatewayMac3", 00);
    int gatewayMac4 = preferences.getInt("gatewayMac4", 00);
    int gatewayMac5 = preferences.getInt("gatewayMac5", 00);
    int gatewayMac6 = preferences.getInt("gatewayMac6", 00);
    String savedTimezone = preferences.getString("timeZone", "ASKT9AKDT,M3.2.0/2:00:00,M11.1.0/2:00:00");
    char macString[18];
    sprintf(macString, "%02X:%02X:%02X:%02X:%02X:%02X",
            gatewayMac1, gatewayMac2, gatewayMac3, gatewayMac4, gatewayMac5, gatewayMac6);
    lv_label_set_text(objects.label_gateway_mac_address, macString);
    set_var_selected_theme(savedTheme);
    set_var_screen_timeout_value(screenTimeout);
    set_var_keep_screen_on_while_driving(keepScreenOnWhileDriving);
    const char *timezoneItems[41] = {"ASKT9AKDT,M3.2.0/2:00:00,M11.1.0/2:00:00", "CST6CDT,M3.2.0/2:00:00,M11.1.0/2:00:00", "MST7MDT,M3.2.0/2:00:00,M11.1.0/2:00:00", "HST11HDT,M3.2.0/2:00:00,M11.1.0/2:00:00", "PST8PDT,M3.2.0/2:00:00,M11.1.0/2:00:00", "EST5EDT,M3.2.0/2:00:00,M11.1.0/2:00:00", "MST7"};
    int selectedTimezone = 0;
    savedTimezone.trim();
    const char *savedTimezoneChar = savedTimezone.c_str();
    for (int i = 0; i < 7; i++)
    {
        if (strcmp(timezoneItems[i],savedTimezoneChar) == 0)
        {
            debugln("Found selected timezone");
            debug("The selected timezone is - ");
            debugln(timezoneItems[i]);
            selectedTimezone = i;
        }
    }
    lv_dropdown_set_selected(objects.drop_down_selected_time_zone, selectedTimezone);
    set_var_current_time_zone_string(savedTimezoneChar);
    // Set the version number label
    lv_label_set_text(objects.label_version_number, CURRENT_VERSION);
}

void loop()
{
    // If settings have changed we need to persist them
    if (get_var_user_settings_changed())
    {
        int selectedTheme = get_var_selected_theme();
        int screenTimeout = get_var_screen_timeout_value();
        bool keepScreenOnWhileDriving = get_var_keep_screen_on_while_driving();
        preferences.putInt("selectedTheme", selectedTheme);
        preferences.putInt("screenTimeout", screenTimeout);
        preferences.putBool("onWhileDriving", keepScreenOnWhileDriving);
        preferences.putInt("gatewayMac1", get_var_gateway_mac_address_byte1());
        preferences.putInt("gatewayMac2", get_var_gateway_mac_address_byte2());
        preferences.putInt("gatewayMac3", get_var_gateway_mac_address_byte3());
        preferences.putInt("gatewayMac4", get_var_gateway_mac_address_byte4());
        preferences.putInt("gatewayMac5", get_var_gateway_mac_address_byte5());
        preferences.putInt("gatewayMac6", get_var_gateway_mac_address_byte6());
        preferences.putString("timeZone", get_var_current_time_zone_string());
        set_var_user_settings_changed(false);
    }
    unsigned long currentStatusCheckMillis = millis();
    if (currentStatusCheckMillis - previousuStatusCheckMillis >= uStatusCheckInterval)
    {
        if ((get_var_pdm01_device01_status() > 0) || (get_var_pdm01_device02_status() > 0) || (get_var_pdm01_device03_status() > 0) || (get_var_pdm01_device04_status() > 0) || (get_var_pdm01_device05_status() > 0) || (get_var_pdm01_device08_status() > 0))
        {
            lv_obj_add_state(objects.label_warning_icon_lights, LV_STATE_CHECKED);
            lv_obj_add_state(objects.label_warning_text_lights, LV_STATE_CHECKED);
        }
        else
        {
            lv_obj_clear_state(objects.label_warning_icon_lights, LV_STATE_CHECKED);
            lv_obj_clear_state(objects.label_warning_text_lights, LV_STATE_CHECKED);
        }
        if (get_var_pdm01_device07_status() > 0)
        {
            lv_obj_add_state(objects.label_warning_icon_water, LV_STATE_CHECKED);
            lv_obj_add_state(objects.label_warning_text_water, LV_STATE_CHECKED);
        }
        else
        {
            lv_obj_clear_state(objects.label_warning_icon_water, LV_STATE_CHECKED);
            lv_obj_clear_state(objects.label_warning_text_water, LV_STATE_CHECKED);
        }
        previousuStatusCheckMillis = currentStatusCheckMillis;
    }
    sleep(1);
}