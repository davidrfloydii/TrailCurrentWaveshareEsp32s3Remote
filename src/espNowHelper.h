#pragma once
#include "globals.h"
#include "secrets.h"
#include <WiFi.h>
#include <esp_wifi.h>
#include <esp_now.h>
#include "ui/vars.h"
// Using the struct similar to ESP32 TWAI driver as a message format. Since all messages
// will be coming from the CAN bus, this makes it easier to parse and use the data and
// expand functionality later.
typedef struct
{
    uint32_t identifier;
    uint8_t data_length_code; /**< Data length code max value of 8 */
    byte dataByte0;
    byte dataByte1;
    byte dataByte2;
    byte dataByte3;
    byte dataByte4;
    byte dataByte5;
    byte dataByte6;
    byte dataByte7;
} esp_now_message_t;

esp_now_peer_info_t peerInfo;
// Create a struct_message to hold incoming CAN message
esp_now_message_t incomingMessage;

uint32_t incomingIdentifier = 0;
uint8_t incomingDLC = 0;
byte incomingDataByte0 = 0;
byte incomingDataByte1 = 0;
byte incomingDataByte2 = 0;
byte incomingDataByte3 = 0;
byte incomingDataByte4 = 0;
byte incomingDataByte5 = 0;
byte incomingDataByte6 = 0;
byte incomingDataByte7 = 0;

// Variable to store if sending data was successful
String success;

namespace espNowHelper
{
    void readMacAddress()
    {
        uint8_t baseMac[6];
        char buffer[100];
        esp_err_t ret = esp_wifi_get_mac(WIFI_IF_STA, baseMac);
        if (ret == ESP_OK)
        {
            Serial.printf("%02x:%02x:%02x:%02x:%02x:%02x\n",
                          baseMac[0], baseMac[1], baseMac[2],
                          baseMac[3], baseMac[4], baseMac[5]);
            snprintf(buffer, sizeof(buffer), "%02x:%02x:%02x:%02x:%02x:%02x", baseMac[0], baseMac[1], baseMac[2],
                     baseMac[3], baseMac[4], baseMac[5]);
            set_var_mcu_mac_address(buffer);
        }
        else
        {
            debugln("Failed to read MAC address");
        }
    }
    // Decode a latitude or longitude float value from a 4-byte array with the first byte as sign
    float decodeLatOrLonValue(const byte in[4])
    {
        uint32_t scaled =
            ((uint32_t)in[1] << 16) |
            ((uint32_t)in[2] << 8) |
            (uint32_t)in[3];

        float f = scaled / 10000.0f;
        if (in[0] == 1)
            f = -f;
        debugln(f, 5);
        return f;
    }
    // Method that can be used to decode date and time data from a CAN message
    void decodeDateTimeData(const byte in[8], uint16_t &year, uint8_t &month, uint8_t &day, uint8_t &hour, uint8_t &minute, uint8_t &second)
    {
        year = ((uint16_t)in[0] << 8) | (uint16_t)in[1];
        month = in[2];
        day = in[3];
        hour = in[4];
        minute = in[5];
        second = in[6];
    }
    // Method that can be used to decode altitude data from a CAN message
    void decodeAltitudeData(const byte in[4])
    {
        double altitude = 0.0;
        uint32_t scaled =
            ((uint32_t)in[0] << 24) |
            ((uint32_t)in[1] << 16) |
            ((uint32_t)in[2] << 8) |
            (uint32_t)in[3];
        altitude = scaled / 100.0;
    }
    // Callback when data is received
    void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len)
    {
        memcpy(&incomingMessage, incomingData, sizeof(incomingMessage));
        // Set variables based on incoming data for indicators as to which pdm devices are
        // currently turned on or have a value > 255
        uint32_t incomingIdentifier = incomingMessage.identifier;
        if (incomingIdentifier == 7)
        {
            // Number of satellites used
            int8_t numSats = incomingMessage.dataByte0;
            set_var_number_of_satellites(numSats);
            // Speed & Course Message
            int32_t scaledSpeed =
                ((uint32_t)incomingMessage.dataByte1 << 8) |
                (uint32_t)incomingMessage.dataByte2;
            float speedKnots = scaledSpeed / 100.0f;
            float speedMph = speedKnots * 1.15078f;
            set_var_current_speed_value((int32_t)speedMph);

            uint32_t scaledCourse =
                ((uint32_t)incomingMessage.dataByte3 << 8) |
                (uint32_t)incomingMessage.dataByte4;
            float courseDegrees = scaledCourse / 100.0f;
            set_var_current_course_over_ground(courseDegrees);
            uint8_t gnssMode = incomingMessage.dataByte5;
            /**
             * @fn getGnssMode
             * @brief Get the used gnss mode
             * @return mode
             * @retval 1  gps
             * @retval 2  beidou
             * @retval 3  gps + beidou
             * @retval 4  glonass
             * @retval 5  gps + glonass
             * @retval 6  beidou +glonass
             * @retval 7  gps + beidou + glonass
             */
            if (gnssMode == 1)
            {
                set_var_gnss_mode("GPS");
            }
            else if (gnssMode == 2)
            {
                set_var_gnss_mode("Beidou");
            }
            else if (gnssMode == 3)
            {
                set_var_gnss_mode("GPS + Beidou");
            }
            else if (gnssMode == 4)
            {
                set_var_gnss_mode("GLONASS");
            }
            else if (gnssMode == 5)
            {
                set_var_gnss_mode("GPS + GLONASS");
            }
            else if (gnssMode == 6)
            {
                set_var_gnss_mode("Beidou + GLONASS");
            }
            else if (gnssMode == 7)
            {
                set_var_gnss_mode("GPS + Beidou + GLONASS");
            }
            else
            {
                set_var_gnss_mode("Unknown");
            }            
        }
        else if (incomingIdentifier == 8)
        {
            uint32_t scaledVoltage =
                ((uint32_t)incomingMessage.dataByte0 << 24) |
                ((uint32_t)incomingMessage.dataByte1 << 16) |
                ((uint32_t)incomingMessage.dataByte2 << 8) |
                (uint32_t)incomingMessage.dataByte3;
        }
        else
        {
            debug("Unknown Identifier: ");
            debugln(incomingIdentifier);
        }
    }

    // Callback when data is sent
    void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status)
    {
        debug("\r\nLast Packet Send Status:\t");
        debugln(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
        if (status == 0)
        {
            success = "Delivery Success :)";
        }
        else
        {
            success = "Delivery Fail :(";
        }
    }

    uint8_t getMacAddress(uint8_t *mac)
    {
        return esp_wifi_get_mac(WIFI_IF_STA, mac);
    }

    void initialize()
    {
        WiFi.mode(WIFI_STA);
        // Init ESP-NOW
        if (esp_now_init() != ESP_OK)
        {
            debugln("Error initializing ESP-NOW");
            return;
        }

        // Once ESPNow is successfully Init, we will register for Send CB to
        // get the status of Trasnmitted packet
        esp_now_register_send_cb(esp_now_send_cb_t(OnDataSent));

        // Register peer
        memcpy(peerInfo.peer_addr, broadcastAddress, 6);
        peerInfo.channel = 0;
        peerInfo.encrypt = false;

        // Add peer
        if (esp_now_add_peer(&peerInfo) != ESP_OK)
        {
            debugln("Failed to add peer");
            return;
        }
        // Register for a callback function that will be called when data is received
        esp_now_register_recv_cb(esp_now_recv_cb_t(OnDataRecv));
        readMacAddress();
    }
}