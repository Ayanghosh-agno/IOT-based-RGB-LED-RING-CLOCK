#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <Adafruit_NeoPixel.h>
#define PIN   14
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);
/* Set these to your desired credentials. */
const char *ssid = "Ayan@Home"; //Enter your WIFI ssid
const char *password = "AG_CO.LTD"; //Enter your WIFI password

ESP8266WebServer server(80);
#include <NTPClient.h>
#include <WiFiUdp.h>
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);


long currentMillis = 0;
long previousMillis = 0;
int interval = 1000;
String formattedDate;
int hour, minute, second;
int hour1, hour2, hour3;

void setup() {
  
  Serial.begin(9600);
  Serial.println();
  Serial.print("Configuring access point...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    
  pixels.begin();
  pixels.setBrightness(50);
  clockSegment();
  pixels.show();

  timeClient.begin();
  timeClient.setTimeOffset(28800);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());


}
void loop() {
  server.handleClient();
   while (!timeClient.update()) {
    timeClient.forceUpdate();
}
currentMillis = millis();
  if (currentMillis - previousMillis > interval) {
    previousMillis = millis();

    // Clear all leds
    pixels.setPixelColor(hour, pixels.Color(0, 0, 0));
    pixels.setPixelColor(hour+1,pixels.Color(0, 0, 0));
    pixels.setPixelColor(hour+2, pixels.Color(0, 0, 0));
    pixels.setPixelColor(hour+3, pixels.Color(0, 0, 0));
    pixels.setPixelColor(hour+4, pixels.Color(0, 0, 0));
    
    pixels.setPixelColor(minute, pixels.Color(0, 0, 0));
    pixels.setPixelColor(second, pixels.Color(0, 0, 0));
    
    pixels.show();

    // The formattedDate comes with the following format:
    // 2018-05-28T16:00:13Z
    formattedDate = timeClient.getFormattedDate();
    Serial.println(formattedDate);

    // Extract time
    hour= formattedDate.substring(11, 13).toInt();
    minute = formattedDate.substring(14, 16).toInt();
    second = formattedDate.substring(17, 19).toInt();
    minute=minute+30;
    hour=hour-2;
    
    
    if(minute>60)
    {
      minute=minute-60;
    }
    if(minute>30)
    {hour=hour-1;
    }
    Serial.println(hour);
    if (hour<0)
    {hour=12+hour;
      
    }
    
   
   
    if (hour > 11) {
      hour = hour - 12;
    }
    hour = (hour * 5) + (minute / 12);
    
    hour1 = hour;
    if (hour == 59) {
      hour2 = hour - 1;
      hour3 = 0;
    }
    else if (hour == 0) {
      hour2 = 59;
      hour3 = hour + 1;
    }
    else {
      hour2 = hour - 1;
      hour3 = hour + 1;
    }
    
    clockSegment();

    pixels.setPixelColor((second), pixels.Color(0, 0, 255));
    pixels.setPixelColor(hour1,pixels.Color(255, 0, 0));
    pixels.setPixelColor(hour2, pixels.Color(255, 0, 0));
    pixels.setPixelColor(hour3,pixels.Color(255, 0, 0));
    pixels.setPixelColor(minute, pixels.Color(0, 255, 0));
    
    pixels.show();
  }
}


void clockSegment()
{
  pixels.setPixelColor(0,pixels.Color (50, 50, 50));
  pixels.setPixelColor(5, pixels.Color (50, 50, 50));
  pixels.setPixelColor(10, pixels.Color (50, 50, 50));
  pixels.setPixelColor(15, pixels.Color (50, 50, 50));
  pixels.setPixelColor(20, pixels.Color (50, 50, 50));
  pixels.setPixelColor(25, pixels.Color (50, 50, 50));
  pixels.setPixelColor(30, pixels.Color (50, 50, 50));
  pixels.setPixelColor(35, pixels.Color (50, 50, 50));
  pixels.setPixelColor(40, pixels.Color (50, 50, 50));
  pixels.setPixelColor(45, pixels.Color (50, 50, 50));
  pixels.setPixelColor(50, pixels.Color (50, 50, 50));
  pixels.setPixelColor(55,pixels.Color (50, 50, 50));
}
