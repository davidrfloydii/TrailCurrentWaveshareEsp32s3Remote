#ifndef EEZ_LVGL_UI_VARS_H
#define EEZ_LVGL_UI_VARS_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// enum declarations



// Flow global variables

enum FlowGlobalVariables {
    FLOW_GLOBAL_VARIABLE_BATTERY_SOC_PERCENTAGE = 0,
    FLOW_GLOBAL_VARIABLE_BATTERY_VOLTAGE = 1,
    FLOW_GLOBAL_VARIABLE_CURRENT_LATITUDE = 2,
    FLOW_GLOBAL_VARIABLE_CURRENT_LONGITUDE = 3,
    FLOW_GLOBAL_VARIABLE_CURRENT_POWER_CONSUMPTION_IN_WATTS = 4,
    FLOW_GLOBAL_VARIABLE_CURRENT_SPEED_VALUE = 5,
    FLOW_GLOBAL_VARIABLE_POWER_TIME_TO_GO_MEASUREMENT = 6,
    FLOW_GLOBAL_VARIABLE_POWER_TIME_TO_GO_MEASUREMENT_TYPE = 7,
    FLOW_GLOBAL_VARIABLE_SHORE_POWER_CONNECTION_STATUS = 8,
    FLOW_GLOBAL_VARIABLE_SOLAR_STATUS = 9,
    FLOW_GLOBAL_VARIABLE_SOLAR_WATTAGE = 10,
    FLOW_GLOBAL_VARIABLE_PDM01_DEVICE01_STATUS = 11,
    FLOW_GLOBAL_VARIABLE_PDM01_DEVICE02_STATUS = 12,
    FLOW_GLOBAL_VARIABLE_PDM01_DEVICE03_STATUS = 13,
    FLOW_GLOBAL_VARIABLE_PDM01_DEVICE04_STATUS = 14,
    FLOW_GLOBAL_VARIABLE_PDM01_DEVICE05_STATUS = 15,
    FLOW_GLOBAL_VARIABLE_PDM01_DEVICE06_STATUS = 16,
    FLOW_GLOBAL_VARIABLE_PDM01_DEVICE07_STATUS = 17,
    FLOW_GLOBAL_VARIABLE_PDM01_DEVICE08_STATUS = 18,
    FLOW_GLOBAL_VARIABLE_MCU_MAC_ADDRESS = 19,
    FLOW_GLOBAL_VARIABLE_NUMBER_OF_SATELLITES = 20,
    FLOW_GLOBAL_VARIABLE_CURRENT_COURSE_OVER_GROUND = 21,
    FLOW_GLOBAL_VARIABLE_GNSS_MODE = 22,
    FLOW_GLOBAL_VARIABLE_CURRENT_ALTITUDE_VALUE = 23,
    FLOW_GLOBAL_VARIABLE_CURRENT_DATE_TIME = 24
};

// Native global variables

extern int32_t get_var_battery_soc_percentage();
extern void set_var_battery_soc_percentage(int32_t value);
extern float get_var_battery_voltage();
extern void set_var_battery_voltage(float value);
extern float get_var_current_latitude();
extern void set_var_current_latitude(float value);
extern float get_var_current_longitude();
extern void set_var_current_longitude(float value);
extern const char *get_var_current_power_consumption_in_watts();
extern void set_var_current_power_consumption_in_watts(const char *value);
extern int32_t get_var_current_speed_value();
extern void set_var_current_speed_value(int32_t value);
extern float get_var_power_time_to_go_measurement();
extern void set_var_power_time_to_go_measurement(float value);
extern const char *get_var_power_time_to_go_measurement_type();
extern void set_var_power_time_to_go_measurement_type(const char *value);
extern const char *get_var_shore_power_connection_status();
extern void set_var_shore_power_connection_status(const char *value);
extern const char *get_var_solar_status();
extern void set_var_solar_status(const char *value);
extern int32_t get_var_solar_wattage();
extern void set_var_solar_wattage(int32_t value);
extern int32_t get_var_pdm01_device01_status();
extern void set_var_pdm01_device01_status(int32_t value);
extern int32_t get_var_pdm01_device02_status();
extern void set_var_pdm01_device02_status(int32_t value);
extern int32_t get_var_pdm01_device03_status();
extern void set_var_pdm01_device03_status(int32_t value);
extern int32_t get_var_pdm01_device04_status();
extern void set_var_pdm01_device04_status(int32_t value);
extern int32_t get_var_pdm01_device05_status();
extern void set_var_pdm01_device05_status(int32_t value);
extern int32_t get_var_pdm01_device06_status();
extern void set_var_pdm01_device06_status(int32_t value);
extern int32_t get_var_pdm01_device07_status();
extern void set_var_pdm01_device07_status(int32_t value);
extern int32_t get_var_pdm01_device08_status();
extern void set_var_pdm01_device08_status(int32_t value);
extern const char *get_var_mcu_mac_address();
extern void set_var_mcu_mac_address(const char *value);
extern int32_t get_var_number_of_satellites();
extern void set_var_number_of_satellites(int32_t value);
extern float get_var_current_course_over_ground();
extern void set_var_current_course_over_ground(float value);
extern const char *get_var_gnss_mode();
extern void set_var_gnss_mode(const char *value);
extern float get_var_current_altitude_value();
extern void set_var_current_altitude_value(float value);
extern const char *get_var_current_date_time();
extern void set_var_current_date_time(const char *value);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_VARS_H*/