#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

String location = "Out"; 
String sensor = "DHT11";
#define DHTPIN 12
#define DHTTYPE    DHT11 
DHT dht(DHTPIN, DHTTYPE);
float temp = 0.0;
float hum = 0.0;
int led = 5;


const char* ssid = "Vierlinden";
const char* password = "Vierlinden1";

//Your Domain name with URL path or IP address with path
String serverName = "http://192.168.178.177/input.php";


void setup() {
  Serial.begin(115200); 
  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);

  dht.begin();
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  digitalWrite(led, LOW);
 
  //Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
}

void loop() {
  temp = dht.readTemperature();
  hum = dht.readHumidity();

//Check WiFi connection status
if(WiFi.status()== WL_CONNECTED){
  WiFiClient client;
  HTTPClient http;

  String Stemp = String(temp);
  String Shum = String(hum);
  Serial.println("temp: " + Stemp);
  Serial.println("hum: " + Shum);
  
  String serverPath = serverName + "?location=" + location + "&sensor=" + sensor + "&temp=" + Stemp + "&hum=" + Shum;
  
  // Your Domain name with URL path or IP address with path
  http.begin(client, serverPath.c_str());
  
  // Send HTTP GET request
  int httpResponseCode = http.GET();
  
  if (httpResponseCode>0) {
    digitalWrite(led, HIGH);
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
delay(100);
digitalWrite(led, LOW);
ESP.deepSleep(3.6e+9); //1h in uS

}
