#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

const char* ssid = "Meine-Fritzbox";
const char* password = "LazurLotta";

//Your Domain name with URL path or IP address with path
String serverName = "http://192.168.178.178/input.php";



void setup() {
  Serial.begin(115200); 

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
 
  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
}

void loop() {

//Check WiFi connection status
if(WiFi.status()== WL_CONNECTED){
  WiFiClient client;
  HTTPClient http;
  
  String serverPath = serverName + "?temp=24.37&hum=12";
  
  // Your Domain name with URL path or IP address with path
  http.begin(client, serverPath.c_str());
  
  // Send HTTP GET request
  int httpResponseCode = http.GET();
  
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    String payload = http.getString();
    Serial.println(payload);
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();
}
else {
  Serial.println("WiFi Disconnected");
}
ESP.deepSleep(6e+7);

}
