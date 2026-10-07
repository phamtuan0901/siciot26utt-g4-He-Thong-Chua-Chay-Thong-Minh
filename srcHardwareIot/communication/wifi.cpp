#include "wifi.h"


const char* WIFI_SSID = "s";
const char* WIFI_PASSWORD = "11111111";

void wifi_init(){
    Serial.println("Ket noi toi  WiFi...");

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println();
    Serial.println("WiFi da ket noi!");
    Serial.print("Dia chi iP: ");
    Serial.println(WiFi.localIP());
}

void wifi_check()
{
    if (WiFi.status() != WL_CONNECTED)
    {
        Serial.println("WiFi khong ket noi!");
        WiFi.reconnect();
    }
}
