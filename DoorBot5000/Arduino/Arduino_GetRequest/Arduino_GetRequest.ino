#include <ESP8266WiFi.h>

#include <ESP8266HTTPClient.h>

//const char * ssid = "Dev DeltaR"; // replace with your wifi ssid and wpa2 key
const char * ssid = "DivIToffice 2.4";
const char * pass = "dajnet66";
const char * url = "http://office.divit.hr:3001/doorbot";

uint8_t LED_Pin = D8; 

WiFiClient client;

void setup() {
    pinMode(LED_Pin, OUTPUT);
    
    Serial.begin(9600);
    delay(10);

   // ConnectToWifi();    
}

void loop() {
    ConnectToWifi();
    
    //Gets buzzer status.
    int value = GetRequest();

    //Check if we want to buzz the door.
    if(value == 1){
        digitalWrite(LED_Pin, HIGH);
        delay(1000);
        digitalWrite(LED_Pin, LOW);
    }
    
    delay(1000);
}

void ConnectToWifi(){
    if(WiFi.status() != WL_CONNECTED){
        WiFi.begin(ssid, pass);
        Serial.println("Connecting to ");
        Serial.println(ssid);
        while (WiFi.status() != WL_CONNECTED) {
            delay(500);
            Serial.print(".");
        }
        Serial.println("");
        Serial.println("WiFi connected");
        Serial.println("IP address: ");
        Serial.println(WiFi.localIP());
    }
}

int GetRequest(){
    HTTPClient http;
    http.begin(url);
    int httpCode = http.GET();
    String payload = http.getString();
    http.end();
    
    //Serial.println("---------------------------------------------------------------------------------");
    //Serial.println(httpCode);
    //Serial.println(payload);
    //Serial.println("---------------------------------------------------------------------------------");
    
    if(httpCode == -1){
        return 0;
    }

    if(payload == "NO"){
        return 0;
    }
    else if(payload == "YES"){
        return 1;
    }

    return 0;
}
