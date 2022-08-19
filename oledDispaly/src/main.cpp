#include <Arduino.h>

#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

const char* ssid = "Meine-Fritzbox";
const char* password = "LazurLotta";

#define NTP_SERVER "de.pool.ntp.org"
#define TZ_INFO "WEST-1DWEST-2,M3.5.0/02:00:00,M10.5.0/03:00:00" // Western European Time

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
//Adafruit_SSD1306 display(OLED_RESET);


int Up = 19;
int Down = 18;
int Left = 17;
int Right = 16;

int buttonStateUp = 0; 
int buttonStateDown = 0; 
int buttonStateLeft = 0; 
int buttonStateRight = 0; 

int ledGreen = 25;
int ledYellow = 26;
int ledRed = 27;

bool offline;
String buttonState;

String app1 = "ntp Sync";
String app2 = "ledMenu";
String app3 = "serverMenu";

String ledApp1 = "All";
String ledApp2 = "Green";
String ledApp3 = "Red";

String serverApp1 = "getTemperature";
String serverApp2 = "getHumidity";
String serverApp3 = "test3";

String widget1 = "tempRoom";
String widget2 = "tempRoom";
String widget3 = "tempRoom";

void drawUi(){
  display.setTextSize(1);
  display.setCursor(0, 56);
  display.print("Anne ist die Beste");
  display.setCursor(0, 0);
  display.print("Digital Watch v0.2");
}

String getButton(){
  String buttonState;

  buttonStateUp = digitalRead(Up);
  buttonStateDown = digitalRead(Down);
  buttonStateLeft = digitalRead(Left);
  buttonStateRight = digitalRead(Right);

  if (buttonStateUp == 1){
    buttonState = "Up";
  }else if (buttonStateDown == 1){
    buttonState = "Down";
  }else if (buttonStateLeft == 1){
    buttonState = "Left";
  }else if (buttonStateRight == 1){
    buttonState = "Right";
  }

  return buttonState;
}

void ntpSync(){
  display.clearDisplay();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  int i = 0;
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
    display.setCursor(10, 20);
    display.print("Connecting to");
    display.setCursor(10, 40);
    display.print(ssid);
    display.display();
    i++;
    if (i>10){
      offline = true;
      display.setCursor(10, 20);
      display.print("Connection failed");
      display.display();
      delay(2000);
      display.clearDisplay();
      break;
    }
  }
  if (WiFi.status() == WL_CONNECTED){
    Serial.println("");
    Serial.print("IP Addresse: ");
    Serial.println(WiFi.localIP());
    Serial.println("Hole NTP Zeit");
    struct tm local;
    configTzTime(TZ_INFO, NTP_SERVER); // ESP32 Systemzeit mit NTP Synchronisieren
    getLocalTime(&local, 10000);      // Versuche 10 s zu Synchronisieren
    WiFi.mode(WIFI_OFF);
  }
  Serial.println("Done");
  display.clearDisplay();
  display.setCursor(55, 20);
  display.println("Done");
  display.display();
  display.clearDisplay();
  digitalWrite(ledGreen, HIGH);
  delay(500);
  digitalWrite(ledGreen, LOW);
}

void drawTime(){
  tm local;
  getLocalTime(&local);
  display.setCursor(10, 20);
  display.setTextSize(3);
  display.print(&local, "%H:%M");
  display.setTextSize(1); 
  display.setCursor(110, 17);
  display.print(&local, "%d");
  display.setCursor(110, 27);
  display.print(&local, "%m"); 
}

void loadingScreen(){
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(20, 0);
  display.print("loading...");
  display.display();
}

float getData(String info, String location){ 
  float data;
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }

  if ((WiFi.status() == WL_CONNECTED)) {
  
    HTTPClient http;
  
    http.begin("http://192.168.178.178/sendData.php?info=" + info + "&location=" + location); 
    int httpCode = http.GET();                                       
  
    if (httpCode > 0) { 
  
        String payload = http.getString();
        //Serial.println(httpCode);
        //Serial.println(payload);
        data = payload.toFloat();
        Serial.println("payload: ");
        Serial.println(data);
      }
  
    else {
      //Serial.println("Error on HTTP request");
      //Serial.println(httpCode);
    }
  
    http.end(); //Free the resources
    WiFi.mode(WIFI_OFF);
    Serial.println("return");
    return (data);
  }
  
}

void humOut(){
  Serial.println("start hum out");
  delay(150);
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(20, 0);
  display.print("Out");
  display.setCursor(20, 20);
  display.print("hum: ");
  display.display();
  display.print("hum");
  display.print("C");
  display.setCursor(82, 41);
  display.print("exit");
  display.drawTriangle(121, 46, 126, 46, 123, 42, 1);
  display.setCursor(82, 49);
  display.print("reload");
  display.drawTriangle(121, 49, 121, 55, 126, 52, 1);
  display.setCursor(82, 57);
  display.print("next");
  display.drawTriangle(121, 58, 123, 62, 126, 58, 1);
  display.display();
  display.clearDisplay();
  while (true){
    delay(150);

    buttonState = getButton();

    if (buttonState == "Right"){

      loadingScreen();

      Serial.println(buttonState);
      display.clearDisplay();
      display.setTextSize(1);
      display.setCursor(20, 0);
      display.print("Out");
      display.setCursor(20, 20);
      display.print("hum: ");
      display.print(getData("hum", "dataOut"));
      display.print("%");
      display.setCursor(82, 41);
      display.print("exit");
      display.drawTriangle(121, 46, 126, 46, 123, 42, 1);
      display.setCursor(82, 49);
      display.print("reload");
      display.drawTriangle(121, 49, 121, 55, 126, 52, 1);
      display.setCursor(82, 57);
      display.print("next");
      display.drawTriangle(121, 58, 123, 62, 126, 58, 1);

      display.display();
      display.clearDisplay();
  }
  if (buttonState == "Up"){
    break;
  }
  if (buttonState == "Down"){
    break;
  }
  }
}

void humWork(){
  Serial.println("start hum work");
  delay(150);
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(20, 0);
  display.print("Work");
  display.setCursor(20, 20);
  display.print("hum: ");
  display.display();
  display.print("hum");
  display.print("%");
  display.setCursor(82, 41);
  display.print("exit");
  display.drawTriangle(121, 46, 126, 46, 123, 42, 1);
  display.setCursor(82, 49);
  display.print("reload");
  display.drawTriangle(121, 49, 121, 55, 126, 52, 1);
  display.setCursor(82, 57);
  display.print("next");
  display.drawTriangle(121, 58, 123, 62, 126, 58, 1);

  display.display();
  display.clearDisplay();
  while (true){
    delay(150);

    buttonState = getButton();

    if (buttonState == "Right"){

      loadingScreen();

      Serial.println(buttonState);
      display.clearDisplay();
      display.setTextSize(1);
      display.setCursor(20, 0);
      display.print("Work");
      display.setCursor(20, 20);
      display.print("temp: ");
      display.print(getData("hum", "dataWork"));
      display.print("%");
      display.setCursor(82, 41);
      display.print("exit");
      display.drawTriangle(121, 46, 126, 46, 123, 42, 1);
      display.setCursor(82, 49);
      display.print("reload");
      display.drawTriangle(121, 49, 121, 55, 126, 52, 1);
      display.setCursor(82, 57);
      display.print("next");
      display.drawTriangle(121, 58, 123, 62, 126, 58, 1);

      display.display();
      display.clearDisplay();
  }
  if (buttonState == "Up"){
    break;
  }
  if (buttonState == "Down"){
    humOut();
    break;
  }
  }
}

void humRoom(){
  delay(150);
  Serial.println("start hum room");
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(20, 0);
  display.print("Room");
  display.setCursor(20, 20);
  display.print("hum: ");
  display.display();
  display.print("hum");
  display.print("C");
  display.setCursor(82, 41);
  display.print("exit");
  display.drawTriangle(121, 46, 126, 46, 123, 42, 1);
  display.setCursor(82, 49);
  display.print("reload");
  display.drawTriangle(121, 49, 121, 55, 126, 52, 1);
  display.setCursor(82, 57);
  display.print("next");
  display.drawTriangle(121, 58, 123, 62, 126, 58, 1);

  display.display();
  display.clearDisplay();
  while (true){
    delay(150);

    buttonState = getButton();

    if (buttonState == "Right"){

      loadingScreen();
      
      Serial.println(buttonState);
      display.clearDisplay();
      display.setTextSize(1);
      display.setCursor(20, 0);
      display.print("Room");
      display.setCursor(20, 20);
      display.print("temp: ");
      display.print(getData("hum", "dataRoom"));
      display.print("C");
      display.setCursor(82, 41);
      display.print("exit");
      display.drawTriangle(121, 46, 126, 46, 123, 42, 1);
      display.setCursor(82, 49);
      display.print("reload");
      display.drawTriangle(121, 49, 121, 55, 126, 52, 1);
      display.setCursor(82, 57);
      display.print("next");
      display.drawTriangle(121, 58, 123, 62, 126, 58, 1);

      display.display();
      display.clearDisplay();
    }
    if (buttonState == "Up"){
      break;
    } else if (buttonState == "Down"){
      humWork();
      break;
    }
  }
}

void tempOut(){
  Serial.println("start temp out");
  delay(150);
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(20, 0);
  display.print("Out");
  display.setCursor(20, 20);
  display.print("temp: ");
  display.display();
  display.print("temp");
  display.print("C");
  display.setCursor(82, 41);
  display.print("exit");
  display.drawTriangle(121, 46, 126, 46, 123, 42, 1);
  display.setCursor(82, 49);
  display.print("reload");
  display.drawTriangle(121, 49, 121, 55, 126, 52, 1);
  display.setCursor(82, 57);
  display.print("next");
  display.drawTriangle(121, 58, 123, 62, 126, 58, 1);
  display.display();
  display.clearDisplay();
  while (true){
    delay(150);

    buttonState = getButton();

    if (buttonState == "Right"){

      loadingScreen();

      Serial.println(buttonState);
      display.clearDisplay();
      display.setTextSize(1);
      display.setCursor(20, 0);
      display.print("Out");
      display.setCursor(20, 20);
      display.print("temp: ");
      display.print(getData("temp", "dataOut"));
      display.print("C");
      display.setCursor(82, 41);
      display.print("exit");
      display.drawTriangle(121, 46, 126, 46, 123, 42, 1);
      display.setCursor(82, 49);
      display.print("reload");
      display.drawTriangle(121, 49, 121, 55, 126, 52, 1);
      display.setCursor(82, 57);
      display.print("next");
      display.drawTriangle(121, 58, 123, 62, 126, 58, 1);

      display.display();
      display.clearDisplay();
  }
  if (buttonState == "Up"){
    break;
  }
  if (buttonState == "Down"){
    break;
  }
  }
}

void tempWork(){
  Serial.println("start temp work");
  delay(150);
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(20, 0);
  display.print("Work");
  display.setCursor(20, 20);
  display.print("temp: ");
  display.display();
  display.print("temp");
  display.print("C");
  display.setCursor(82, 41);
  display.print("exit");
  display.drawTriangle(121, 46, 126, 46, 123, 42, 1);
  display.setCursor(82, 49);
  display.print("reload");
  display.drawTriangle(121, 49, 121, 55, 126, 52, 1);
  display.setCursor(82, 57);
  display.print("next");
  display.drawTriangle(121, 58, 123, 62, 126, 58, 1);

  display.display();
  display.clearDisplay();
  while (true){
    delay(150);

    buttonState = getButton();

    if (buttonState == "Right"){

      loadingScreen();

      Serial.println(buttonState);
      display.clearDisplay();
      display.setTextSize(1);
      display.setCursor(20, 0);
      display.print("Work");
      display.setCursor(20, 20);
      display.print("temp: ");
      display.print(getData("temp", "dataWork"));
      display.print("C");
      display.setCursor(82, 41);
      display.print("exit");
      display.drawTriangle(121, 46, 126, 46, 123, 42, 1);
      display.setCursor(82, 49);
      display.print("reload");
      display.drawTriangle(121, 49, 121, 55, 126, 52, 1);
      display.setCursor(82, 57);
      display.print("next");
      display.drawTriangle(121, 58, 123, 62, 126, 58, 1);

      display.display();
      display.clearDisplay();
  }
  if (buttonState == "Up"){
    break;
  }
  if (buttonState == "Down"){
    tempOut();
    break;
  }
  }
}

void tempRoom(){
  delay(150);
  Serial.println("start temp room");
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(20, 0);
  display.print("Room");
  display.setCursor(20, 20);
  display.print("temp: ");
  display.display();
  display.print("temp");
  display.print("C");
  display.setCursor(82, 41);
  display.print("exit");
  display.drawTriangle(121, 46, 126, 46, 123, 42, 1);
  display.setCursor(82, 49);
  display.print("reload");
  display.drawTriangle(121, 49, 121, 55, 126, 52, 1);
  display.setCursor(82, 57);
  display.print("next");
  display.drawTriangle(121, 58, 123, 62, 126, 58, 1);

  display.display();
  display.clearDisplay();
  while (true){
    delay(150);

    buttonState = getButton();

    if (buttonState == "Right"){

      loadingScreen();
      
      Serial.println(buttonState);
      display.clearDisplay();
      display.setTextSize(1);
      display.setCursor(20, 0);
      display.print("Room");
      display.setCursor(20, 20);
      display.print("temp: ");
      display.print(getData("temp", "dataRoom"));
      display.print("C");
      display.setCursor(82, 41);
      display.print("exit");
      display.drawTriangle(121, 46, 126, 46, 123, 42, 1);
      display.setCursor(82, 49);
      display.print("reload");
      display.drawTriangle(121, 49, 121, 55, 126, 52, 1);
      display.setCursor(82, 57);
      display.print("next");
      display.drawTriangle(121, 58, 123, 62, 126, 58, 1);

      display.display();
      display.clearDisplay();
    }
    if (buttonState == "Up"){
      break;
    } else if (buttonState == "Down"){
      tempWork();
      break;
    }
  }
}

void showButton(){
  display.setCursor(0, 30);
  display.print(getButton());
}

void blinkAll(){
  display.clearDisplay();
  display.display();
  display.setTextSize(1);
  display.setCursor(10, 20);
  display.print("green: 0");
  display.setCursor(10, 30);
  display.print("yellow: 0");
  display.setCursor(10, 40);
  display.print("red: 0");
  display.display();
  delay(500);
  display.clearDisplay();
  digitalWrite(ledGreen, HIGH);
  display.setCursor(10, 20);
  display.print("green: 1");
  display.setCursor(10, 30);
  display.print("yellow: 0");
  display.setCursor(10, 40);
  display.print("red: 0");
  display.display();
  delay(500);
  display.clearDisplay();
  digitalWrite(ledYellow, HIGH);
  display.setCursor(10, 20);
  display.print("green: 1");
  display.setCursor(10, 30);
  display.print("yellow: 1");
  display.setCursor(10, 40);
  display.print("red: 0");
  display.display();
  delay(500);
  display.clearDisplay();
  digitalWrite(ledRed, HIGH);
  display.setCursor(10, 20);
  display.print("green: 1");
  display.setCursor(10, 30);
  display.print("yellow: 1");
  display.setCursor(10, 40);
  display.print("red: 1");
  display.display();
  delay(500);
  display.clearDisplay();
  digitalWrite(ledGreen, LOW);
  display.setCursor(10, 20);
  display.print("green: 0");
  display.setCursor(10, 30);
  display.print("yellow: 1");
  display.setCursor(10, 40);
  display.print("red: 1");
  display.display();
  delay(400);
  display.clearDisplay();
  digitalWrite(ledYellow, LOW);
  display.setCursor(10, 20);
  display.print("green: 0");
  display.setCursor(10, 30);
  display.print("yellow: 0");
  display.setCursor(10, 40);
  display.print("red: 1");
  display.display();
  delay(500);
  display.clearDisplay();
  digitalWrite(ledRed, LOW);
  display.setCursor(10, 20);
  display.print("green: 0");
  display.setCursor(10, 30);
  display.print("yellow: 0");
  display.setCursor(10, 40);
  display.print("red: 0");
  display.display();
  delay(500);
  display.clearDisplay();
}

void blinkGreen(){
  for (int i = 0; i<3; i++){
    digitalWrite(ledGreen, HIGH);
    delay(500);
    digitalWrite(ledGreen, LOW);
    delay(500);
  }
}
void blinkRed(){
  for (int i = 0; i<3; i++){
    digitalWrite(ledRed, HIGH);
    delay(500);
    digitalWrite(ledRed, LOW);
    delay(500);
  }
}

void ledMenu(){
  delay(1000);
  int run = 1;
  int i = 0;
  display.setTextSize(1);
  while (run == 1){
    display.setCursor(0, 0);
    display.print(i);
    display.setCursor(20, 0);
    display.print("ledMenu");
    switch(i){
      case 0:
        display.setCursor(10, 20);
        display.print("-");
        display.setCursor(20, 20);
        display.print(ledApp1);
        display.setCursor(20, 32);
        display.print(ledApp2);
        display.setCursor(20, 44);
        display.print(ledApp3);
        display.setCursor(20, 56);
        display.print("exit");
        break;
      case 1:
        display.setTextSize(1);
        display.setCursor(10, 32);
        display.print("-");
        display.setCursor(20, 20);
        display.print(ledApp1);
        display.setCursor(20, 32);
        display.print(ledApp2);
        display.setCursor(20, 44);
        display.print(ledApp3);
        display.setCursor(20, 56);
        display.print("exit");
        break;
      case 2:
        display.setCursor(10, 44);
        display.print("-");
        display.setCursor(20, 20);
        display.print(ledApp1);
        display.setCursor(20, 32);
        display.print(ledApp2);
        display.setCursor(20, 44);
        display.print(ledApp3);
        display.setCursor(20, 56);
        display.print("exit");
        break;
      case 3:
        display.setCursor(10, 56);
        display.print("-");
        display.setCursor(20, 20);
        display.print(ledApp1);
        display.setCursor(20, 32);
        display.print(ledApp2);
        display.setCursor(20, 44);
        display.print(ledApp3);
        display.setCursor(20, 56);
        display.print("exit");
        break;   
    }
    
    buttonState = getButton();

    if (buttonState == "Down"){
      i++;
    }else if(buttonState == "Up"){
      i--;
    }
    if(i == 4){
        i = 0;
    }
    if(i == -1){
        i = 3;
    }

    if(buttonState == "Left"){
      run = 0;
    }else if(buttonState == "Right" && i == 3){
      run = 0;
    }else if(buttonState == "Right" && i == 0){
      blinkAll();
    }else if(buttonState == "Right" && i == 1){
      blinkGreen();
    }else if(buttonState == "Right" && i == 2){
      blinkRed();
    }
  
    display.display();
    display.clearDisplay();
    delay(150);
    
  }
}

void serverMenu(){
  delay(1000);
  int run = 1;
  int i = 0;
  display.setTextSize(1);
  while (run == 1){
    display.setCursor(0, 0);
    display.print(i);
    display.setCursor(20, 0);
    display.print("serverMenu");
    switch(i){
      case 0:
        display.setCursor(10, 20);
        display.print("-");
        display.setCursor(20, 20);
        display.print(serverApp1);
        display.setCursor(20, 32);
        display.print(serverApp2);
        display.setCursor(20, 44);
        display.print(serverApp3);
        display.setCursor(20, 56);
        display.print("exit");
        break;
      case 1:
        display.setTextSize(1);
        display.setCursor(10, 32);
        display.print("-");
        display.setCursor(20, 20);
        display.print(serverApp1);
        display.setCursor(20, 32);
        display.print(serverApp2);
        display.setCursor(20, 44);
        display.print(serverApp3);
        display.setCursor(20, 56);
        display.print("exit");
        break;
      case 2:
        display.setCursor(10, 44);
        display.print("-");
        display.setCursor(20, 20);
        display.print(serverApp1);
        display.setCursor(20, 32);
        display.print(serverApp2);
        display.setCursor(20, 44);
        display.print(serverApp3);
        display.setCursor(20, 56);
        display.print("exit");
        break;
      case 3:
        display.setCursor(10, 56);
        display.print("-");
        display.setCursor(20, 20);
        display.print(serverApp1);
        display.setCursor(20, 32);
        display.print(serverApp2);
        display.setCursor(20, 44);
        display.print(serverApp3);
        display.setCursor(20, 56);
        display.print("exit");
        break;   
    }
    
    buttonState = getButton();

    if (buttonState == "Down"){
      i++;
    }else if(buttonState == "Up"){
      i--;
    }
    if(i == 4){
        i = 0;
    }
    if(i == -1){
        i = 3;
    }

    if(buttonState == "Left"){
      run = 0;
    }else if(buttonState == "Right" && i == 3){
      run = 0;
    }else if(buttonState == "Right" && i == 0){
      tempRoom();
    }else if(buttonState == "Right" && i == 1){
      humRoom();

    }else if(buttonState == "Right" && i == 2){

    }
  
    display.display();
    display.clearDisplay();
    delay(150);
    
  }
}

void menu(){
  delay(1000);
  int run = 1;
  int i = 0;
  display.setTextSize(1);
  while (run == 1){
    display.setCursor(0, 0);
    display.print(i);
    display.setCursor(20, 0);
    display.print("Menu");
    switch(i){
      case 0:
        display.setCursor(10, 20);
        display.print("-");
        display.setCursor(20, 20);
        display.print(app1);
        display.setCursor(20, 32);
        display.print(app2);
        display.setCursor(20, 44);
        display.print(app3);
        display.setCursor(20, 56);
        display.print("exit");
        break;
      case 1:
        display.setTextSize(1);
        display.setCursor(10, 32);
        display.print("-");
        display.setCursor(20, 20);
        display.print(app1);
        display.setCursor(20, 32);
        display.print(app2);
        display.setCursor(20, 44);
        display.print(app3);
        display.setCursor(20, 56);
        display.print("exit");
        break;
      case 2:
        display.setCursor(10, 44);
        display.print("-");
        display.setCursor(20, 20);
        display.print(app1);
        display.setCursor(20, 32);
        display.print(app2);
        display.setCursor(20, 44);
        display.print(app3);
        display.setCursor(20, 56);
        display.print("exit");
        break;
      case 3:
        display.setCursor(10, 56);
        display.print("-");
        display.setCursor(20, 20);
        display.print(app1);
        display.setCursor(20, 32);
        display.print(app2);
        display.setCursor(20, 44);
        display.print(app3);
        display.setCursor(20, 56);
        display.print("exit");
        break;   
    }
    buttonState = getButton();
    
    if (buttonState == "Down"){
      i++;
    }else if(buttonState == "Up"){
      i--;
    }
    if(i == 4){
        i = 0;
    }
    if(i == -1){
        i = 3;
    }

    if(buttonState == "Left"){
      run = 0;
    }else if(buttonState == "Right" && i == 3){
      run = 0;
    }else if(buttonState == "Right" && i == 0){
      ntpSync();
    }else if(buttonState == "Right" && i == 1){
      ledMenu();
    }else if(buttonState == "Right" && i == 2){
      serverMenu();
    }
  
    display.display();
    display.clearDisplay();
    delay(150);
    
  }
}

void handleButton(){
  String buttonState;
  buttonState = getButton();
  if (buttonState == "Up"){

  }else if (buttonState == "Down"){
    tempRoom();

  }else if (buttonState == "Left"){
    
  }else if (buttonState == "Right"){
    menu();
  }

}

void setup() {
  Serial.begin(9600);
  
  //setenv("TZ", TZ_INFO, 1);             
  //tzset();

  pinMode(Up, INPUT);
  pinMode(Down, INPUT);
  pinMode(Left, INPUT);
  pinMode(Right, INPUT);

pinMode(ledGreen, OUTPUT); 
pinMode(ledYellow, OUTPUT); 
pinMode(ledRed, OUTPUT);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
  Serial.println(F("SSD1306 allocation failed"));
  for(;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(WHITE); // Draw white text
  display.setCursor(0, 0);  
  display.display();
  ntpSync();

}

void loop() {
  delay(100);
  drawUi();
  drawTime();
  handleButton();
  display.display();
  display.clearDisplay();
}