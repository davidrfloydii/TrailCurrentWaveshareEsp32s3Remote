#include <Arduino.h>
#include <string.h>
#include "ui/screens.h"
#include "ui/vars.h"


int32_t solar_wattage;
int32_t get_var_solar_wattage() {
    return solar_wattage;
}
void set_var_solar_wattage(int32_t value) {
    solar_wattage = value;
}

char solar_status[100] = { 0 };
const char *get_var_solar_status() {
    return solar_status;
}

void set_var_solar_status(const char *value) {
    strncpy(solar_status, value, sizeof(solar_status) / sizeof(char));
    solar_status[sizeof(solar_status) / sizeof(char) - 1] = 0;
}



char shore_power_connection_status[100] = { 0 };
const char *get_var_shore_power_connection_status() {
    return shore_power_connection_status;
}

void set_var_shore_power_connection_status(const char *value) {
    strncpy(shore_power_connection_status, value, sizeof(shore_power_connection_status) / sizeof(char));
    shore_power_connection_status[sizeof(shore_power_connection_status) / sizeof(char) - 1] = 0;
}



int32_t pdm01_device08_status;
int32_t get_var_pdm01_device08_status() {
    return pdm01_device08_status;
}
void set_var_pdm01_device08_status(int32_t value) {
    pdm01_device08_status = value;
}


int32_t pdm01_device07_status;
int32_t get_var_pdm01_device07_status() {
    return pdm01_device07_status;
}
void set_var_pdm01_device07_status(int32_t value) {
    pdm01_device07_status = value;
}


int32_t pdm01_device06_status;
int32_t get_var_pdm01_device06_status() {
    return pdm01_device06_status;
}
void set_var_pdm01_device06_status(int32_t value) {
    pdm01_device06_status = value;
}


int32_t pdm01_device05_status;
int32_t get_var_pdm01_device05_status() {
    return pdm01_device05_status;
}
void set_var_pdm01_device05_status(int32_t value) {
    pdm01_device05_status = value;
}

int32_t pdm01_device04_status;
int32_t get_var_pdm01_device04_status() {
    return pdm01_device04_status;
}
void set_var_pdm01_device04_status(int32_t value) {
    pdm01_device04_status = value;
}

int32_t pdm01_device03_status;
int32_t get_var_pdm01_device03_status() {
    return pdm01_device03_status;
}
void set_var_pdm01_device03_status(int32_t value) {
    pdm01_device03_status = value;
}

int32_t pdm01_device02_status;
int32_t get_var_pdm01_device02_status() {
    return pdm01_device02_status;
}
void set_var_pdm01_device02_status(int32_t value) {
    pdm01_device02_status = value;
}

int32_t pdm01_device01_status;
int32_t get_var_pdm01_device01_status() {
    return pdm01_device01_status;
}
void set_var_pdm01_device01_status(int32_t value) {
    pdm01_device01_status = value;
}

float battery_voltage;
float get_var_battery_voltage() {
    return battery_voltage;
}
void set_var_battery_voltage(float value) {
    battery_voltage = value;
}

int32_t battery_soc_percentage;
int32_t get_var_battery_soc_percentage() {
    return battery_soc_percentage;
}
void set_var_battery_soc_percentage(int32_t value) {
    battery_soc_percentage = value;
}

char current_power_consumption_in_watts[100] = { 0 };
const char *get_var_current_power_consumption_in_watts() {
    return current_power_consumption_in_watts;
}
void set_var_current_power_consumption_in_watts(const char *value) {
    strncpy(current_power_consumption_in_watts, value, sizeof(current_power_consumption_in_watts) / sizeof(char));
    current_power_consumption_in_watts[sizeof(current_power_consumption_in_watts) / sizeof(char) - 1] = 0;
    lv_label_set_text(objects.label_remaining_cacpity_1, current_power_consumption_in_watts);
}

int32_t current_speed_value;
int32_t get_var_current_speed_value() {
    return current_speed_value;
}
void set_var_current_speed_value(int32_t value) {
    current_speed_value = value;
    lv_label_set_text(objects.label_current_speed_value, String(value).c_str());
}