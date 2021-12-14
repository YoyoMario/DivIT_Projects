#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

//const char * ssid = "Dev DeltaR"; // replace with your wifi ssid and wpa2 key
//const char * ssid = "DivIToffice 2.4";
const char * ssid = "DivitMesh";
const char * password = "dajnet66";
//const char * password = "dajnet66";
const char * url = "http://office.divit.hr:3001/doorbot";

uint8_t LED_Pin = 15; 

WiFiClient client;

void setup() {
  Serial.begin(115200);         // Start the Serial communication to send messages to the computer
  pinMode(LED_Pin, OUTPUT);
  delay(10);
  ConnectToWifi();
}

void loop()
{
  if(WiFi.status() == WL_CONNECTED)
  {
    //Gets buzzer status.
    int value = GetRequest();

    //Check if we want to buzz the door.
    if(value == 1)
    {
        digitalWrite(LED_Pin, HIGH);
        delay(1000);
        digitalWrite(LED_Pin, LOW);
    }
    else
    {
      delay(1000);  
    }
  }
}

void ConnectToWifi()
{
  Serial.println('\n');
  
  WiFi.begin(ssid, password);             // Connect to the network
  Serial.print("Connecting to ");
  Serial.print(ssid); Serial.println(" ...");

  int i = 0;
  while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
    delay(1000);
    Serial.print(++i); Serial.print(' ');
  }

  Serial.println('\n');
  Serial.println("Connection established!");  
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());         // Send the IP address of the ESP8266 to the computer
}

int GetRequest(){
    HTTPClient http;
    http.begin(client, url);
    int httpCode = http.GET();
    String payload = http.getString();
    http.end();
    
    Serial.println("---------------------------------------------------------------------------------");
    Serial.println(httpCode);
    Serial.println(payload);
    Serial.println("---------------------------------------------------------------------------------");
    
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
