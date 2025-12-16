#include <Arduino.h>
#include "globals.h"
#include "ui/ui.h"
#include "ui/actions.h"
#include "ui/screens.h"
#include "ui/styles.h"

void action_change_screen(lv_event_t *e)
{
    Serial.print("Changing screen to ID: ");
    Serial.println((int)lv_event_get_user_data(e));
    int screenData = (int)lv_event_get_user_data(e);
    /* Clear all toolbar button checked states for all home buttons */
    lv_obj_clear_state(objects.home_page_bottom_nav_bar__bottom_nav_bar_button_home, LV_STATE_CHECKED);
    lv_obj_clear_state(objects.trailer_page_bottom_nav_bar__bottom_nav_bar_button_home, LV_STATE_CHECKED);
    lv_obj_clear_state(objects.power_page_bottom_nav_bar__bottom_nav_bar_button_home, LV_STATE_CHECKED);
    lv_obj_clear_state(objects.solar_page_bottom_nav_bar__bottom_nav_bar_button_home, LV_STATE_CHECKED);
    lv_obj_clear_state(objects.air_page_bottom_nav_bar__bottom_nav_bar_button_home, LV_STATE_CHECKED);
    lv_obj_clear_state(objects.setting_page_bottom_nav_bar__bottom_nav_bar_button_home, LV_STATE_CHECKED);
    /* Clear all toolbar button checked states for all trailer buttons */
    lv_obj_clear_state(objects.home_page_bottom_nav_bar__bottom_nav_bar_button_trailer, LV_STATE_CHECKED);
    lv_obj_clear_state(objects.trailer_page_bottom_nav_bar__bottom_nav_bar_button_trailer, LV_STATE_CHECKED);
    lv_obj_clear_state(objects.power_page_bottom_nav_bar__bottom_nav_bar_button_trailer, LV_STATE_CHECKED);
    lv_obj_clear_state(objects.solar_page_bottom_nav_bar__bottom_nav_bar_button_trailer, LV_STATE_CHECKED);
    lv_obj_clear_state(objects.air_page_bottom_nav_bar__bottom_nav_bar_button_trailer, LV_STATE_CHECKED);
    lv_obj_clear_state(objects.setting_page_bottom_nav_bar__bottom_nav_bar_button_trailer, LV_STATE_CHECKED);
    /* Clear all toolbar button checked states for all power buttons */
    lv_obj_clear_state(objects.home_page_bottom_nav_bar__botttom_nav_bar_button_power, LV_STATE_CHECKED);
    lv_obj_clear_state(objects.trailer_page_bottom_nav_bar__botttom_nav_bar_button_power, LV_STATE_CHECKED);
    lv_obj_clear_state(objects.power_page_bottom_nav_bar__botttom_nav_bar_button_power, LV_STATE_CHECKED);
    lv_obj_clear_state(objects.solar_page_bottom_nav_bar__botttom_nav_bar_button_power, LV_STATE_CHECKED);
    lv_obj_clear_state(objects.air_page_bottom_nav_bar__botttom_nav_bar_button_power, LV_STATE_CHECKED);
    lv_obj_clear_state(objects.setting_page_bottom_nav_bar__botttom_nav_bar_button_power, LV_STATE_CHECKED);
    /* Clear all toolbar button checked states for all solar buttons */
    lv_obj_clear_state(objects.home_page_bottom_nav_bar__botttom_nav_bar_button_solar, LV_STATE_CHECKED);
    lv_obj_clear_state(objects.trailer_page_bottom_nav_bar__botttom_nav_bar_button_solar, LV_STATE_CHECKED);
    lv_obj_clear_state(objects.power_page_bottom_nav_bar__botttom_nav_bar_button_solar, LV_STATE_CHECKED);
    lv_obj_clear_state(objects.solar_page_bottom_nav_bar__botttom_nav_bar_button_solar, LV_STATE_CHECKED);
    lv_obj_clear_state(objects.air_page_bottom_nav_bar__botttom_nav_bar_button_solar, LV_STATE_CHECKED);
    lv_obj_clear_state(objects.setting_page_bottom_nav_bar__botttom_nav_bar_button_solar, LV_STATE_CHECKED);
    /* Clear all toolbar button checked states for all settings buttons */
    lv_obj_clear_state(objects.home_page_bottom_nav_bar__botttom_nav_bar_button_settings, LV_STATE_CHECKED);
    lv_obj_clear_state(objects.trailer_page_bottom_nav_bar__botttom_nav_bar_button_settings, LV_STATE_CHECKED);
    lv_obj_clear_state(objects.power_page_bottom_nav_bar__botttom_nav_bar_button_settings, LV_STATE_CHECKED);
    lv_obj_clear_state(objects.solar_page_bottom_nav_bar__botttom_nav_bar_button_settings, LV_STATE_CHECKED);
    lv_obj_clear_state(objects.air_page_bottom_nav_bar__botttom_nav_bar_button_settings, LV_STATE_CHECKED);
    lv_obj_clear_state(objects.setting_page_bottom_nav_bar__botttom_nav_bar_button_settings, LV_STATE_CHECKED);

    if (screenData == 0)
    {
        lv_scr_load(objects.home);
        /* Set toolbar icons on home to checked state */
        lv_obj_add_state(objects.home_page_bottom_nav_bar__bottom_nav_bar_button_home, LV_STATE_CHECKED);
    }
    else if (screenData == 1)
    {
        lv_scr_load(objects.trailer);
        /* Set toolbar icons on trailer to checked state */
        lv_obj_add_state(objects.trailer_page_bottom_nav_bar__bottom_nav_bar_button_trailer, LV_STATE_CHECKED);
    }
    else if (screenData == 2)
    {
        lv_scr_load(objects.power);
        /* Set toolbar icons on power to checked state */
        lv_obj_add_state(objects.power_page_bottom_nav_bar__botttom_nav_bar_button_power, LV_STATE_CHECKED);
    }
    else if (screenData == 3)
    {
        lv_scr_load(objects.solar);
        /* Set toolbar icons on solar to checked state */
        lv_obj_add_state(objects.solar_page_bottom_nav_bar__botttom_nav_bar_button_solar, LV_STATE_CHECKED);
    }
    else if (screenData == 4)
    {
        lv_scr_load(objects.air);
        /* Set toolbar icons on air to checked state */
        lv_obj_add_state(objects.air_page_bottom_nav_bar__botttom_nav_bar_button_fridge, LV_STATE_CHECKED);
    }
    else if (screenData == 5)
    {
        lv_scr_load(objects.settings);
        /* Set toolbar icons on settings to checked state */
        lv_obj_add_state(objects.setting_page_bottom_nav_bar__botttom_nav_bar_button_settings, LV_STATE_CHECKED);
    }
}
