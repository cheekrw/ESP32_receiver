/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp-now-esp32-arduino-ide/

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

//Roger Cheek notes feb/march 2021
//This runs on an feather huzzah32 and recieves temp data from a remote V8 trigboard
//Data is sent only when the trigboard detects a change in the temp.
//the trigboard has the mac addr of the target esp32 running this code.
//It uses ESP NOW to communicate.
//The remote trigboard does not wait for confirmation, as this would take time and battery

#include <esp_now.h>
#include <WiFi.h>

int stored_transmission_num = 0;
int error_count = 0;

// Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
//    char a[32];
    int b;
    String c;
    String d;
//    bool e;
} struct_message;

// Create a struct_message called myData
struct_message myData;

// callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Bytes received: ");
  Serial.print(len);
//  Serial.print("Char: ");
//  Serial.println(myData.a);
//  Serial.print("Int: ");
//  Serial.println(myData.b);
  Serial.print(" .  Battery (V): ");
  Serial.print(myData.c);
  Serial.print(" .  Temperature (F): ");
  Serial.println(myData.d);
//  Serial.print("Bool: ");
//  Serial.println(myData.e);
//  Serial.println();
//  if (stored_transmission_num != myData.b) {
//    if (stored_transmission_num != 0 ) {
//    error_count++;
//    }
//  }
//  Serial.print("Missed transmissions: ");
//  Serial.println(error_count);
//  stored_transmission_num = myData.b + 1;
}

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);

  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {

}
