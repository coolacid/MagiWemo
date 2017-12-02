#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <IRrecv.h>
#include "wemo.h"
#include "wemo-switch.h"
// #include <ArduinoJson.h>

// Use turn on the save buffer feature for more complete capture coverage.
IRrecv irrecv(RECV_PIN, CAPTURE_BUFFER_SIZE, TIMEOUT, true);

#define ENABLE_MagiQuest 

decode_results results;

unsigned long debounceTime;

void setup()
{
  Serial.begin(115200);
  Serial.println();

  WiFi.begin(Wifi_Name, Wifi_Pass);

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());

  irrecv.enableIRIn(); // Start the receiver
  debounceTime = millis();
}

void loop() {
  if ( irrecv.decode(&results) ) {
    if (results.decode_type == MAGIQUEST) {
      Serial.printf("Decoded MAGIQUEST - Magnitude=%d, ID=0x", results.command, results.address);
      Serial.printf("%X\n", results.value);
      if (millis() - debounceTime > debounceDelay) {
        int state = getState();
        int sig = getSignal();
        String name = getName();
        Serial.printf("State: %i\n", state);
        Serial.printf("Name: %s\n", name.c_str());
        Serial.printf("Signal: %i\n", sig);
        if (state == 0) {
          Serial.println("Turn On!");
          switchON();
        } else {
          Serial.println("Turn Off!");
          switchOFF();
        }
        irrecv.resume(); // Receive the next value
        Serial.println();
        debounceTime = millis();
      } else {
        Serial.println("Debounced!");
      }
    }
  }
}
