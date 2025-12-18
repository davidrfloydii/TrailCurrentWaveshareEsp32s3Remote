#ifndef EEZ_LVGL_UI_EVENTS_H
#define EEZ_LVGL_UI_EVENTS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void action_change_screen(lv_event_t * e);
extern void action_settings_selection_change(lv_event_t * e);
extern void action_change_theme(lv_event_t * e);
extern void action_timeout_changed(lv_event_t * e);
extern void action_keep_on_while_driving_changed(lv_event_t * e);
extern void action_change_gateway_mac_address(lv_event_t * e);
extern void action_commit_mac_address_changes(lv_event_t * e);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_EVENTS_H*/