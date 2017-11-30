#ifndef WEMO_H_
#define WEMO_H_

// Pin where IR receiver is
const int RECV_PIN = D5;

// Wemo Settings
const char Wemo_IP[] = "";
const int Wemo_Port = 49153;

// Wifi Settings
const char Wifi_Name[] = "";
const char Wifi_Pass[] = "";

// Do Not Edit!

const unsigned long debounceDelay = 5000; 

// As this program is a special purpose capture/decoder, let us use a larger
// than normal buffer so we can handle Air Conditioner remote codes.
const uint16_t CAPTURE_BUFFER_SIZE = 1024;

// Nr. of milli-Seconds of no-more-data before we consider a message ended.
// NOTE: Don't exceed MAX_TIMEOUT_MS. Typically 130ms.
#define TIMEOUT 15U  // Suits most messages, while not swallowing repeats.
// #define TIMEOUT 90U  // Suits messages with big gaps like XMP-1 & some aircon
                        // units, but can accidently swallow repeated messages
                        // in the rawData[] output.



#endif // WEMO_H_