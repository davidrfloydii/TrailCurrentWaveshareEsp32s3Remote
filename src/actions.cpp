#include <Arduino.h>
#include "globals.h"
#include "ui/ui.h"
#include "ui/actions.h"
#include "ui/screens.h"
#include "ui/styles.h"
#include "ui/vars.h"

void action_settings_selection_change(lv_event_t *e)
{
    int menuSelection = (int)lv_event_get_user_data(e);
    lv_obj_add_flag(objects.container_display_settings, LV_OBJ_FLAG_HIDDEN);     // Hide by default
    lv_obj_add_flag(objects.container_connectivity_options, LV_OBJ_FLAG_HIDDEN); // Hide by default
    lv_obj_add_flag(objects.container_demo_settings, LV_OBJ_FLAG_HIDDEN);        // Hide by default
    lv_obj_add_flag(objects.container_about_settings, LV_OBJ_FLAG_HIDDEN);       // Hide by default
    if (menuSelection == 0)
    {
        lv_obj_clear_flag(objects.container_display_settings, LV_OBJ_FLAG_HIDDEN);
    }
    else if (menuSelection == 1)
    {
        lv_obj_clear_flag(objects.container_connectivity_options, LV_OBJ_FLAG_HIDDEN);
    }
    else if (menuSelection == 2)
    {
        lv_obj_clear_flag(objects.container_demo_settings, LV_OBJ_FLAG_HIDDEN);
    }
    else if (menuSelection == 3)
    {
        lv_obj_clear_flag(objects.container_about_settings, LV_OBJ_FLAG_HIDDEN);
    }
}

void action_change_theme(lv_event_t *e)
{
    set_var_user_settings_changed(true);
    int themeIndex = (int)lv_event_get_user_data(e);
    set_var_selected_theme(themeIndex);
}

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

void action_timeout_changed(lv_event_t *e)
{
    set_var_user_settings_changed(true);
    int currentTimeoutValue = get_var_screen_timeout_value();
    int eventValue = (int)lv_event_get_user_data(e);
    if (eventValue == 0)
    {
        currentTimeoutValue--;
    }
    else
    {
        currentTimeoutValue++;
    }
    set_var_screen_timeout_value(currentTimeoutValue);
}

void action_keep_on_while_driving_changed(lv_event_t *e)
{
    set_var_user_settings_changed(true);
    bool keepScreenOnWhileDriving = lv_obj_has_state(objects.check_box_keep_screen_on_while_in_motion, LV_STATE_CHECKED);
    debug("Keep on?");
    debugln(keepScreenOnWhileDriving);
    set_var_keep_screen_on_while_driving(keepScreenOnWhileDriving);
}

static void ta_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *ta = lv_event_get_target(e);
    //lv_obj_t * ta = lv_event_get_target_obj(e);
    lv_obj_t * kb = (lv_obj_t *)lv_event_get_user_data(e);
    debugln(code);
    if(code == LV_EVENT_FOCUSED) {
        lv_keyboard_set_textarea(kb, ta);
        lv_obj_clear_flag(kb, LV_OBJ_FLAG_HIDDEN);
    }

    if(code == LV_EVENT_DEFOCUSED) {
        lv_keyboard_set_textarea(kb, NULL);
        lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
    }

    if (code == 31) {
        lv_obj_add_flag(objects.container_mac_addr_entry,LV_OBJ_FLAG_HIDDEN);
    }
}

void action_change_gateway_mac_address(lv_event_t *e)
{
    lv_obj_clear_flag(objects.container_mac_addr_entry,LV_OBJ_FLAG_HIDDEN);
    /*Create a keyboard to use it with an of the text areas*/
    lv_obj_t *kb = lv_keyboard_create(objects.container_mac_addr_entry);
    lv_obj_set_size(kb,800,375);
    /*Create a text area. The keyboard will write here*/

    lv_obj_add_event_cb(objects.text_box_mac_address_input, ta_event_cb, LV_EVENT_ALL, kb);
    lv_keyboard_set_textarea(kb, objects.text_box_mac_address_input);
    lv_obj_add_state(objects.text_box_mac_address_input,LV_STATE_FOCUSED);
}
