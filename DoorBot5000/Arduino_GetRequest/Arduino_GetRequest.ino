#include <ESP8266WiFi.h>

#include <ESP8266HTTPClient.h>

const char * ssid = "Dev DeltaR"; // replace with your wifi ssid and wpa2 key
const char * pass = "dajnet66";
const char * url = "http://office.divit.hr:3000/";

WiFiClient client;

void setup() {
    Serial.begin(9600);
    delay(10);

    Serial.println("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, pass);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void loop() {
    HTTPClient http;
    http.begin(url);
    int httpCode = http.GET();
    String payload = http.getString();

    Serial.println(httpCode);
    Serial.println(payload);

    http.end();

    delay(10000);
}
