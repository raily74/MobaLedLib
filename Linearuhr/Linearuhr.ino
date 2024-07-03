/*
  Project: Linearuhr von NTC Zeit Server mit ESP32
  Author: Michael Todtenbier
  Date: Created 02.07.2024
  Version: V1.0
  IDE: Arduino IDE 1.8.19

  Required libraries (sketch -> include library -> manage libraries)
  -Grüße aus Flensburg
*/

#include <WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
//#include <Adafruit_NeoPixel.h>
#include <FastLED.h>

#define DATA_PIN 27 // Pin für LED-Streifen
const byte NUM_LEDS = 14; // Anzahl der WS2811-Chips
// This is an array of leds. One item for each led in your strip.
CRGB leds[NUM_LEDS];

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 7200, 60000);

// Wi-Fi Settings
const char *wifi_ssid = "YourSSID";
const char *wifi_password = "YourPassword";
const char* NTP_SERVER = "de.pool.ntp.org";
const char* TZ_INFO = "CET-1CEST-2,M3.5.0/02:00:00,M10.5.0/03:00:00";

/*
  time_t now;
  tm tm;
*/

void setup () {
  Serial.begin(115200);

  // Verbindung zu WiFi herstellen
  delay(10);
  WiFi.begin(wifi_ssid, wifi_password);
  int counter = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    if (++counter > 100) ESP.restart();
    Serial.print(".");
  }
  Serial.println("WiFi connected");

  //FastLED aktivieren
  FastLED.addLeds<WS2811, DATA_PIN, GRB>(leds, NUM_LEDS);

  // NTP Client starten
  timeClient.begin();
}

void loop () {
  timeClient.update();

  byte hoursH = timeClient.getHours() / 10;
  byte hoursL = timeClient.getHours() % 10;
  byte minutesH = timeClient.getMinutes() / 10;
  byte minutesL = timeClient.getMinutes() % 10;
  byte secondsH = timeClient.getSeconds() / 10;
  byte secondsL = timeClient.getSeconds() % 10;

//  Serial.printf(" \tUhrzeit: %02d:%02d:%02d \n", hours, minutes, seconds);
  for (int i = 0; i < NUM_LEDS; i++)leds[i] = CRGB::Black;


  //Zehnerstunden
  if (hoursH > 1) leds[13] = CRGB::Yellow;
  else if (hoursH ) leds[13] = CRGB::Red;

  //Einerstunden
  if (hoursL > 8) {leds[12] = CRGB::White; leds[11] = CRGB::White; leds[10] = CRGB::White;}
  else if (hoursL > 7) {leds[12] = CRGB::Yellow; leds[11] = CRGB::White; leds[10] = CRGB::White;}
  else if (hoursL > 6) {leds[12] = CRGB::Red; leds[11] = CRGB::White; leds[10] = CRGB::White;}
  else if (hoursL > 5) {leds[11] = CRGB::White; leds[10] = CRGB::White;}
  else if (hoursL > 4) {leds[11] = CRGB::Yellow; leds[10] = CRGB::White;}
  else if (hoursL > 3) {leds[11] = CRGB::Red; leds[10] = CRGB::White;}
  else if (hoursL > 2) leds[10] = CRGB::White;
  else if (hoursL > 1) leds[10] = CRGB::Yellow;
  else if (hoursL )leds[10] = CRGB::Red;


  //Zehnerminuten
  if ( minutesH > 4) {leds[9] = CRGB::Yellow; leds[8] = CRGB::White;}
  else if ( minutesH > 3) {leds[9] = CRGB::Red; leds[8] = CRGB::White;}
  else if ( minutesH > 2) leds[8] = CRGB::White;
  else if ( minutesH > 1) leds[8] = CRGB::Yellow;
  else if ( minutesH ) leds[8] = CRGB::Red;

  //Einerminuten
  if ( minutesL > 8) {leds[7] = CRGB::White; leds[6] = CRGB::White; leds[5] = CRGB::White;}
  else if ( minutesL > 7) {leds[7] = CRGB::Yellow; leds[6] = CRGB::White; leds[5] = CRGB::White;}
  else if ( minutesL > 6) {leds[7] = CRGB::Red; leds[6] = CRGB::White; leds[5] = CRGB::White;}
  else if ( minutesL > 5) {leds[6] = CRGB::White; leds[5] = CRGB::White;}
  else if ( minutesL > 4) {leds[6] = CRGB::Yellow; leds[5] = CRGB::White;}
  else if ( minutesL > 3) {leds[6] = CRGB::Red; leds[5] = CRGB::White;}
  else if ( minutesL > 2) leds[5] = CRGB::White;
  else if ( minutesL > 1) leds[5] = CRGB::Yellow;
  else if ( minutesL )leds[5] = CRGB::Red;


  //Zehnersekunden
  if (secondsH > 4) {leds[4] = CRGB::Yellow; leds[3] = CRGB::White;}
  else if (secondsH > 3) {leds[4] = CRGB::Red; leds[3] = CRGB::White;}
  else if (secondsH > 2) leds[3] = CRGB::White;
  else if (secondsH > 1) leds[3] = CRGB::Yellow;
  else if (secondsH) leds[3] = CRGB::Red;

  //Einersekunden
  if (secondsL > 8) {leds[2] = CRGB::White; leds[1] = CRGB::White; leds[0] = CRGB::White;}
  else if (secondsL > 7) {leds[2] = CRGB::Yellow; leds[1] = CRGB::White; leds[0] = CRGB::White;}
  else if (secondsL > 6) {leds[2] = CRGB::Red; leds[1] = CRGB::White; leds[0] = CRGB::White;}
  else if (secondsL > 5) {leds[1] = CRGB::White; leds[0] = CRGB::White;}
  else if (secondsL > 4) {leds[1] = CRGB::Yellow; leds[0] = CRGB::White;}
  else if (secondsL > 3) {leds[1] = CRGB::Red; leds[0] = CRGB::White;}
  else if (secondsL > 2) leds[0] = CRGB::White;
  else if (secondsL > 1) leds[0] = CRGB::Yellow;
  else if (secondsL) leds[0] = CRGB::Red;

  FastLED.show();
  FastLED.delay(1000);
}
