#include <Arduino.h>
#include "globals.h"
#include <string.h>
#include "ui/screens.h"
#include "ui/vars.h"
#include <time.h>
#include <sys/time.h>

char date_time_utc[100] = {0};
char date_time_local[100] = {0};

// Portable timegm() replacement
time_t my_timegm(struct tm *tm)
{
    char *old_tz = getenv("TZ");
    char *saved_tx = NULL;

    if (old_tz)
    {
        saved_tx = strdup(old_tz);
    }
    setenv("TZ", "UTC0", 1);
    tzset();
    tm->tm_isdst = 0;

    time_t t = mktime(tm);
    // TODO: Move time zone to settings and save to NVM
    setenv("TZ", "CST6CDT,M3.2.0,M11.1.0", 1);
    tzset();
    debug("TIME: ");
    debugln(tm->tm_hour);
    debugln(tm->tm_mday);
    return t;
}

int32_t solar_wattage;
int32_t get_var_solar_wattage()
{
    return solar_wattage;
}
void set_var_solar_wattage(int32_t value)
{
    solar_wattage = value;
}

char solar_status[100] = {0};
const char *get_var_solar_status()
{
    return solar_status;
}

void set_var_solar_status(const char *value)
{
    strncpy(solar_status, value, sizeof(solar_status) / sizeof(char));
    solar_status[sizeof(solar_status) / sizeof(char) - 1] = 0;
}

char shore_power_connection_status[100] = {0};
const char *get_var_shore_power_connection_status()
{
    return shore_power_connection_status;
}

void set_var_shore_power_connection_status(const char *value)
{
    strncpy(shore_power_connection_status, value, sizeof(shore_power_connection_status) / sizeof(char));
    shore_power_connection_status[sizeof(shore_power_connection_status) / sizeof(char) - 1] = 0;
}

int32_t pdm01_device01_status;
int32_t get_var_pdm01_device01_status()
{
    return pdm01_device01_status;
}
void set_var_pdm01_device01_status(int32_t value)
{
    pdm01_device01_status = value;
    if (value > 0)
    {
        lv_obj_add_state(objects.lbl_device01_status_ind, LV_STATE_CHECKED);
        lv_obj_add_state(objects.btn_device01, LV_STATE_CHECKED);
        lv_obj_add_state(objects.lbl_device01_label, LV_STATE_CHECKED);
    }
    else
    {
        lv_obj_clear_state(objects.btn_device01, LV_STATE_CHECKED);
        lv_obj_clear_state(objects.lbl_device01_status_ind, LV_STATE_CHECKED);
        lv_obj_clear_state(objects.lbl_device01_label, LV_STATE_CHECKED);
    }
}

int32_t pdm01_device02_status;
int32_t get_var_pdm01_device02_status()
{
    return pdm01_device02_status;
}
void set_var_pdm01_device02_status(int32_t value)
{
    pdm01_device02_status = value;
    if (value > 0)
    {
        lv_obj_add_state(objects.lbl_device02_status_ind, LV_STATE_CHECKED);
        lv_obj_add_state(objects.btn_device02, LV_STATE_CHECKED);
        lv_obj_add_state(objects.lbl_device02_label, LV_STATE_CHECKED);
    }
    else
    {
        lv_obj_clear_state(objects.btn_device02, LV_STATE_CHECKED);
        lv_obj_clear_state(objects.lbl_device02_status_ind, LV_STATE_CHECKED);
        lv_obj_clear_state(objects.lbl_device02_label, LV_STATE_CHECKED);
    }
}

int32_t pdm01_device03_status;
int32_t get_var_pdm01_device03_status()
{
    return pdm01_device03_status;
}
void set_var_pdm01_device03_status(int32_t value)
{
    pdm01_device03_status = value;
    if (value > 0)
    {
        lv_obj_add_state(objects.lbl_device03_status_ind, LV_STATE_CHECKED);
        lv_obj_add_state(objects.btn_device03, LV_STATE_CHECKED);
        lv_obj_add_state(objects.lbl_device03_label, LV_STATE_CHECKED);
    }
    else
    {
        lv_obj_clear_state(objects.btn_device03, LV_STATE_CHECKED);
        lv_obj_clear_state(objects.lbl_device03_status_ind, LV_STATE_CHECKED);
        lv_obj_clear_state(objects.lbl_device03_label, LV_STATE_CHECKED);
    }
}

int32_t pdm01_device04_status;
int32_t get_var_pdm01_device04_status()
{
    return pdm01_device04_status;
}
void set_var_pdm01_device04_status(int32_t value)
{
    pdm01_device04_status = value;
    if (value > 0)
    {
        lv_obj_add_state(objects.lbl_device04_status_ind, LV_STATE_CHECKED);
        lv_obj_add_state(objects.btn_device04, LV_STATE_CHECKED);
        lv_obj_add_state(objects.lbl_device04_label, LV_STATE_CHECKED);
    }
    else
    {
        lv_obj_clear_state(objects.btn_device04, LV_STATE_CHECKED);
        lv_obj_clear_state(objects.lbl_device04_status_ind, LV_STATE_CHECKED);
        lv_obj_clear_state(objects.lbl_device04_label, LV_STATE_CHECKED);
    }
}

int32_t pdm01_device05_status;
int32_t get_var_pdm01_device05_status()
{
    return pdm01_device05_status;
}
void set_var_pdm01_device05_status(int32_t value)
{
    pdm01_device05_status = value;
    if (value > 0)
    {
        lv_obj_add_state(objects.lbl_device05_status_ind, LV_STATE_CHECKED);
        lv_obj_add_state(objects.btn_device05, LV_STATE_CHECKED);
        lv_obj_add_state(objects.lbl_device05_label, LV_STATE_CHECKED);
    }
    else
    {
        lv_obj_clear_state(objects.btn_device05, LV_STATE_CHECKED);
        lv_obj_clear_state(objects.lbl_device05_status_ind, LV_STATE_CHECKED);
        lv_obj_clear_state(objects.lbl_device05_label, LV_STATE_CHECKED);
    }
}

int32_t pdm01_device06_status;
int32_t get_var_pdm01_device06_status()
{
    return pdm01_device06_status;
}
void set_var_pdm01_device06_status(int32_t value)
{
    pdm01_device06_status = value;
    if (value > 0)
    {
        lv_obj_add_state(objects.lbl_device06_status_ind, LV_STATE_CHECKED);
        lv_obj_add_state(objects.btn_device06, LV_STATE_CHECKED);
        lv_obj_add_state(objects.lbl_device06_label, LV_STATE_CHECKED);
    }
    else
    {
        lv_obj_clear_state(objects.btn_device06, LV_STATE_CHECKED);
        lv_obj_clear_state(objects.lbl_device06_status_ind, LV_STATE_CHECKED);
        lv_obj_clear_state(objects.lbl_device06_label, LV_STATE_CHECKED);
    }
}

int32_t pdm01_device07_status;
int32_t get_var_pdm01_device07_status()
{
    return pdm01_device07_status;
}
void set_var_pdm01_device07_status(int32_t value)
{
    pdm01_device07_status = value;
    if (value > 0)
    {
        lv_obj_add_state(objects.lbl_device07_status_ind, LV_STATE_CHECKED);
        lv_obj_add_state(objects.btn_device07, LV_STATE_CHECKED);
        lv_obj_add_state(objects.lbl_device07_label, LV_STATE_CHECKED);
    }
    else
    {
        lv_obj_clear_state(objects.btn_device07, LV_STATE_CHECKED);
        lv_obj_clear_state(objects.lbl_device07_status_ind, LV_STATE_CHECKED);
        lv_obj_clear_state(objects.lbl_device07_label, LV_STATE_CHECKED);
    }
}

int32_t pdm01_device08_status;
int32_t get_var_pdm01_device08_status()
{
    return pdm01_device08_status;
}
void set_var_pdm01_device08_status(int32_t value)
{
    pdm01_device08_status = value;
    if (value > 0)
    {
        lv_obj_add_state(objects.lbl_device08_status_ind, LV_STATE_CHECKED);
        lv_obj_add_state(objects.btn_device08, LV_STATE_CHECKED);
        lv_obj_add_state(objects.lbl_device08_label, LV_STATE_CHECKED);
    }
    else
    {
        lv_obj_clear_state(objects.btn_device08, LV_STATE_CHECKED);
        lv_obj_clear_state(objects.lbl_device08_status_ind, LV_STATE_CHECKED);
        lv_obj_clear_state(objects.lbl_device08_label, LV_STATE_CHECKED);
    }
}

float battery_voltage;
float get_var_battery_voltage()
{
    return battery_voltage;
}
void set_var_battery_voltage(float value)
{
    battery_voltage = value;
}

int32_t battery_soc_percentage;
int32_t get_var_battery_soc_percentage()
{
    return battery_soc_percentage;
}
void set_var_battery_soc_percentage(int32_t value)
{
    battery_soc_percentage = value;
}

char current_power_consumption_in_watts[100] = {0};
const char *get_var_current_power_consumption_in_watts()
{
    return current_power_consumption_in_watts;
}
void set_var_current_power_consumption_in_watts(const char *value)
{
    strncpy(current_power_consumption_in_watts, value, sizeof(current_power_consumption_in_watts) / sizeof(char));
    current_power_consumption_in_watts[sizeof(current_power_consumption_in_watts) / sizeof(char) - 1] = 0;
    lv_label_set_text(objects.label_remaining_cacpity_1, current_power_consumption_in_watts);
}

int32_t current_speed_value;
int32_t get_var_current_speed_value()
{
    return current_speed_value;
}
void set_var_current_speed_value(int32_t value)
{
    current_speed_value = value;
    lv_label_set_text(objects.label_current_speed_value, String(value).c_str());
}

char mcu_mac_address[100] = {0};
const char *get_var_mcu_mac_address()
{
    return mcu_mac_address;
}
void set_var_mcu_mac_address(const char *value)
{
    strncpy(mcu_mac_address, value, sizeof(mcu_mac_address) / sizeof(char));
    mcu_mac_address[sizeof(mcu_mac_address) / sizeof(char) - 1] = 0;
    lv_label_set_text(objects.mcu_mac_address_value, value);
}

int32_t number_of_satellites;
int32_t get_var_number_of_satellites()
{
    return number_of_satellites;
}
void set_var_number_of_satellites(int32_t value)
{
    number_of_satellites = value;
    lv_label_set_text(objects.label_number_of_satellite_value, String(value).c_str());
}

float current_course_over_ground;
float get_var_current_course_over_ground()
{
    return current_course_over_ground;
}
void set_var_current_course_over_ground(float value)
{
    current_course_over_ground = value;
}

char gnss_mode[100] = {0};
const char *get_var_gnss_mode()
{
    return gnss_mode;
}
void set_var_gnss_mode(const char *value)
{
    strncpy(gnss_mode, value, sizeof(gnss_mode) / sizeof(char));
    gnss_mode[sizeof(gnss_mode) / sizeof(char) - 1] = 0;
    lv_label_set_text(objects.gnss_mode_value, value);
}

float current_altitude_value;
float get_var_current_altitude_value()
{
    return current_altitude_value;
}
void set_var_current_altitude_value(float value)
{
    current_altitude_value = value;
    lv_label_set_text(objects.label_altitude_in_feet_value, String(value).c_str());
}

float current_latitude;
float get_var_current_latitude()
{
    return current_latitude;
}
void set_var_current_latitude(float value)
{
    current_latitude = value;
    char latString[16];
    dtostrf(value, 10, 6, latString);
    lv_label_set_text(objects.label_current_lat_value, latString);
}

float current_longitude;
float get_var_current_longitude()
{
    return current_longitude;
}
void set_var_current_longitude(float value)
{
    current_longitude = value;
    char lonString[16];
    dtostrf(value, 11, 6, lonString);
    lv_label_set_text(objects.label_current_long_value, lonString);
}

char current_date_time[100] = {0};
const char *get_var_current_date_time()
{
    return current_date_time;
}
void set_var_current_date_time(const char *value)
{
    // Save UTC string
    strncpy(date_time_utc, value, sizeof(date_time_utc));
    date_time_utc[sizeof(date_time_utc) - 1] = '\0';

    struct tm tm_utc = {0};

    if (strptime(date_time_utc, "%Y-%m-%d %H:%M:%S", &tm_utc) != NULL)
    {

        // Convert parsed UTC → time_t
        time_t t_utc = my_timegm(&tm_utc);

        // Convert to local time zone
        struct tm *tm_local = localtime(&t_utc);
        // TODO: Move formatting to settings and save to NVM
        // Format into local time string
        strftime(date_time_local,
                 sizeof(date_time_local),
                 "%m/%d/%Y %I:%M %p",
                 tm_local);
    }
    else
    {
        date_time_local[0] = '\0'; // parsing failed
    }
    lv_label_set_text(objects.label_current_date_time_value, date_time_local);
}