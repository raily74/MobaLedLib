/*
  Project:  Linearuhr von NTC Zeit Server mit ESP32
  Author:   Michael Todtenbier
  Date:     Created 02.07.2024
  Version:  V1.0
  IDE:      Arduino IDE 1.8.19

  Required libraries (sketch -> include library -> manage libraries)
  -
*/

#include <WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
//#include <Adafruit_NeoPixel.h>
#include <FastLED.h>

#define DATA_PIN  27 // Pin für LED-Streifen
#define NUM_LEDS  14 // Anzahl der WS2811-Chips
// This is an array of leds.  One item for each led in your strip.
CRGB leds[NUM_LEDS];

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 7200, 60000);

// Wi-Fi Settings
const char *wifi_ssid = "raily74";
const char *wifi_password = "2q$Wh+3Tm6vKk/]$usAsx66J";
const char* NTP_SERVER = "de.pool.ntp.org";
const char* TZ_INFO    = "CET-1CEST-2,M3.5.0/02:00:00,M10.5.0/03:00:00";

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

  leds[0] = CRGB::White;
     FastLED.show();
  leds[1] = CRGB::White;
     FastLED.show();
  leds[2] = CRGB::White;
     FastLED.show();
  leds[3] = CRGB::White;
     FastLED.show();
  leds[4] = CRGB::White;
     FastLED.show();
  leds[5] = CRGB::White;
     FastLED.show();
  leds[6] = CRGB::White;
     FastLED.show();
  leds[7] = CRGB::White;
     FastLED.show();
  leds[8] = CRGB::White;
     FastLED.show();
  leds[9] = CRGB::White;
     FastLED.show();
  leds[10] = CRGB::White;
     FastLED.show();
  leds[11] = CRGB::White;
     FastLED.show();
  leds[12] = CRGB::White;
     FastLED.show();
  leds[13] = CRGB::White;
     FastLED.show();
  delay(2000);
  leds[0] = CRGB::Black;
     FastLED.show();
  leds[1] = CRGB::Black;
     FastLED.show();
  leds[2] = CRGB::Black;
     FastLED.show();
  leds[3] = CRGB::Black;
     FastLED.show();
  leds[4] = CRGB::Black;
     FastLED.show();
  leds[5] = CRGB::Black;
     FastLED.show();
  leds[6] = CRGB::Black;
     FastLED.show();
  leds[7] = CRGB::Black;
     FastLED.show();
  leds[8] = CRGB::Black;
     FastLED.show();
  leds[9] = CRGB::Black;
     FastLED.show();
  leds[10] = CRGB::Black;
     FastLED.show();
  leds[11] = CRGB::Black;
     FastLED.show();
  leds[12] = CRGB::Black;
     FastLED.show();
  leds[13] = CRGB::Black;
     FastLED.show();
  delay(2000);
/*
  // LED-Streifen initialisieren
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
*/
}

/*
// Funktion zum Setzen der LEDs basierend auf der Zeit
void setTimeLEDs(int value, int startChip, int chipCount, uint32_t color) {
  int activeChips = map(value, 0, 59, 0, chipCount);
  for (int i = 0; i < chipCount; i++) {
    if (i < activeChips) {
      strip.setPixelColor(startChip + i, color);
    } else {
      strip.setPixelColor(startChip + i, strip.Color(0, 0, 0));
    }
  }
}
*/

void loop () {

  timeClient.update();

  int hours = timeClient.getHours();
  int minutes = timeClient.getMinutes();
  int seconds = timeClient.getSeconds();

  Serial.printf(" \tUhrzeit: %02d:%02d:%02d \n", hours, minutes, seconds);
               
  //Zehnerstunden
  if (((hours / 10) % 10) > 1) {
     leds[13] = CRGB::Yellow;
     FastLED.show();
          
  }
  
  else if (((hours / 10) % 10) > 0) {
     leds[13] = CRGB::Red;
     FastLED.show();

  }
 
  else {
     leds[13] = CRGB::Black;
     FastLED.show();
}
     
  //Einerstunden
  if ((hours % 10) > 8) {
     leds[12] = CRGB::White;
     FastLED.show();
  }

  else if ((hours % 10) > 7) {
     leds[12] = CRGB::Yellow;
     FastLED.show();
  }

  else if ((hours % 10) > 6) {
     leds[12] = CRGB::Red;
     FastLED.show();
  }
  
  else if ((hours % 10) > 5) {
     leds[11] = CRGB::White;
     FastLED.show();
  }
  else if ((hours % 10) > 4) {
     leds[11] = CRGB::Yellow;
     FastLED.show();
  }

  else if ((hours % 10) > 3) {
     leds[11] = CRGB::Red;
     FastLED.show();
  }
  
  else if ((hours % 10) > 2) {
     leds[10] = CRGB::White;
     FastLED.show();
  }

  else if ((hours % 10) > 1) {
     leds[10] = CRGB::Yellow;
     FastLED.show();
  }

  else if ((hours % 10) > 0) {
     leds[10] = CRGB::Red;
     FastLED.show();
  }
   
  else {
     leds[12] = CRGB::Black;
     FastLED.show();
     leds[11] = CRGB::Black;
     FastLED.show();
     leds[10] = CRGB::Black;
     FastLED.show();
}

  //Zehnerminuten
  if (((minutes / 10) % 10) > 4) {
     leds[9] = CRGB::Yellow;
     FastLED.show();
  }
  
  else if (((minutes / 10) % 10) > 3) {
     leds[9] = CRGB::Red;
     FastLED.show();
  }
  
  else if (((minutes / 10) % 10) > 2) {
     leds[8] = CRGB::White;
     FastLED.show();
  }
  
  else if (((minutes / 10) % 10) > 1) {
     leds[8] = CRGB::Yellow;
     FastLED.show();
          
  }
  
  else if (((minutes / 10) % 10) > 0) {
     leds[8] = CRGB::Red;
     FastLED.show();

  }
 
  else {
     leds[9] = CRGB::Black;
     FastLED.show();
     leds[8] = CRGB::Black;
     FastLED.show();
}
     
  //Einerminuten
  if ((minutes % 10) > 8) {
     leds[7] = CRGB::White;
     FastLED.show();
  }

  else if ((minutes % 10) > 7) {
     leds[7] = CRGB::Yellow;
     FastLED.show();
  }

  else if ((minutes % 10) > 6) {
     leds[7] = CRGB::Red;
     FastLED.show();
  }
  
  else if ((minutes % 10) > 5) {
     leds[6] = CRGB::White;
     FastLED.show();
  }
  else if ((minutes % 10) > 4) {
     leds[6] = CRGB::Yellow;
     FastLED.show();
  }

  else if ((minutes % 10) > 3) {
     leds[6] = CRGB::Red;
     FastLED.show();
  }
  
  else if ((minutes % 10) > 2) {
     leds[5] = CRGB::White;
     FastLED.show();
  }

  else if ((minutes % 10) > 1) {
     leds[5] = CRGB::Yellow;
     FastLED.show();
  }

  else if ((minutes % 10) > 0) {
     leds[5] = CRGB::Red;
     FastLED.show();
  }
   
  else {
     leds[7] = CRGB::Black;
     FastLED.show();
     leds[6] = CRGB::Black;
     FastLED.show();
     leds[5] = CRGB::Black;
     FastLED.show();

}
  //Zehnersekunden
  if (((seconds / 10) % 10) > 4) {
     leds[4] = CRGB::Yellow;
     FastLED.show();
  }
  
  else if (((seconds / 10) % 10) > 3) {
     leds[4] = CRGB::Red;
     FastLED.show();
  }
  
  else if (((seconds / 10) % 10) > 2) {
     leds[3] = CRGB::White;
     FastLED.show();
  }
  
  else if (((seconds / 10) % 10) > 1) {
     leds[3] = CRGB::Yellow;
     FastLED.show();
          
  }
  
  else if (((seconds / 10) % 10) > 0) {
     leds[3] = CRGB::Red;
     FastLED.show();

  }
 
  else {
     leds[3] = CRGB::Black;
     FastLED.show();
     leds[4] = CRGB::Black;
     FastLED.show();
}
     
  //Einersekunden
  if ((seconds % 10) > 8) {
     leds[2] = CRGB::White;
     FastLED.show();
  }

  else if ((seconds % 10) > 7) {
     leds[2] = CRGB::Yellow;
     FastLED.show();
  }

  else if ((seconds % 10) > 6) {
     leds[2] = CRGB::Red;
     FastLED.show();
  }
  
  else if ((seconds % 10) > 5) {
     leds[1] = CRGB::White;
     FastLED.show();
  }
  else if ((seconds % 10) > 4) {
     leds[1] = CRGB::Yellow;
     FastLED.show();
  }

  else if ((seconds % 10) > 3) {
     leds[1] = CRGB::Red;
     FastLED.show();
  }
  
  else if ((seconds % 10) > 2) {
     leds[0] = CRGB::White;
     FastLED.show();
  }

  else if ((seconds % 10) > 1) {
     leds[0] = CRGB::Yellow;
     FastLED.show();
  }

  else if ((seconds % 10) > 0) {
     leds[0] = CRGB::Red;
     FastLED.show();
  }
   
  else {
     leds[2] = CRGB::Black;
     FastLED.show();
     leds[1] = CRGB::Black;
     FastLED.show();
     leds[0] = CRGB::Black;
     FastLED.show();
}
}
