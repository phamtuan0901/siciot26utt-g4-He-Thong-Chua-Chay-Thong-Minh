<<<<<<< HEAD
#include "wifi.h"
=======
#include "wifi_manager.h"
>>>>>>> 5a27bb5f4ca3a0af90cb0ed49142c28bbe9d02e8

const char* WIFI_SSID = "TEN_WIFI";
const char* WIFI_PASSWORD = "MAT_KHAU_WIFI";

void wifi_init()
{
    Serial.println("Connecting to WiFi...");

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println();
    Serial.println("WiFi connected!");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}

void wifi_check()
{
    if (WiFi.status() != WL_CONNECTED)
    {
        Serial.println("WiFi disconnected!");
        WiFi.reconnect();
    }
}
