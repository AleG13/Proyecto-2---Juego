
#include <ESP8266WiFi.h>
#include <espnow.h>

#include "pitches.h"

struct PacketData
{
  byte xAxisValue;
  byte yAxisValue;
  byte switchPressed;
};
PacketData receiverData;

const int buzzerPin = 14; //for Arduino Microcontroller
bool throttleAndSteeringMode = false;

void beep(int note, int duration){
  tone(buzzerPin, note, duration);
  delay(duration);
  noTone(buzzerPin);
}

void OnDataRecv( uint8_t *mac_addr,  uint8_t *data, uint8_t data_len){
  // Procesa los datos recibidos aquí
  if (data_len == 0)
  {
    return;
  }
  memcpy(&receiverData, data, sizeof(receiverData));
  String inputData ;
   inputData = receiverData.xAxisValue;
  Serial.print(inputData); 
  Serial.print(" "); 
  inputData = receiverData.yAxisValue;
  Serial.println(inputData); 
}



void setup() {
  Serial.begin(115200);
  pinMode(buzzerPin, OUTPUT);
  // Inicializa WiFi
  WiFi.mode(WIFI_STA);
 

  // Inicializa ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("There was an error initializing ESP-NOW");
    return;
  }
  
  // Once the ESP-Now protocol is initialized, we will register the callback function
  // to be able to react when a package arrives in near to real time without pooling every loop.
 
}
int cancion = 0;
void loop() {
   esp_now_register_recv_cb(OnDataRecv);
  if (Serial.available() > 0) {
    cancion = Serial.read();
  }

switch (cancion){
  case 49:
  beep(NOTE_E6, 125);
  beep(NOTE_E6, 125);
  beep(NOTE_G6, 250);
  beep(NOTE_E6, 250);
  beep(NOTE_G6, 250);
  beep(NOTE_E6, 125);
  beep(NOTE_E6, 125);
  beep(NOTE_G6, 250);
  beep(NOTE_E6, 250);
  beep(NOTE_G6, 250);
   beep(NOTE_E6, 125);
  beep(NOTE_E6, 125);
  beep(NOTE_G6, 250);
  beep(NOTE_E6, 250);
  beep(NOTE_G6, 250);
 

  beep(NOTE_FS6, 125);
  beep(NOTE_G6, 125);
  beep(NOTE_F6, 125);
  beep(NOTE_E6, 125);
  beep(NOTE_D6, 125);
  beep(NOTE_C6, 125);
  beep(NOTE_B5, 125);

  beep(NOTE_C6, 125);
  beep(NOTE_D6, 125);
  beep(NOTE_E6, 125);
  beep(NOTE_F6, 125);
  beep(NOTE_FS6, 125);
  beep(NOTE_G6, 125);
  beep(NOTE_A6, 125);
  beep(NOTE_B6, 250);

  beep(NOTE_F6, 125);
  beep(NOTE_G6, 125);
  beep(NOTE_F6, 125);
  beep(NOTE_A5, 125);
  beep(NOTE_D6, 250);
  break;


  case 50:
  
  beep(NOTE_D4, 60);
  delay(20);
  beep(NOTE_D4, 60);
  delay(100);
 
  break;

  case 51:
  
  beep(NOTE_A4, 60);
  beep(NOTE_GS4, 60);
  delay(500);
  
  beep(NOTE_B4, 100);
  beep(NOTE_F5, 125);
  delay(20);
  beep(NOTE_F5, 125);
  beep(NOTE_F5, 125);
  beep(NOTE_E5, 125);
  beep(NOTE_D5, 125);
  beep(NOTE_E4, 125);
  beep(NOTE_G3, 125);
  beep(NOTE_E4, 125);
  beep(NOTE_C4, 250);


 
  break;

  case 52:
  
  beep(NOTE_G4, 125);
  beep(NOTE_C5, 125);
  beep(NOTE_E5, 125);
  beep(NOTE_G5, 125);
  beep(NOTE_C6, 125);
  beep(NOTE_E6, 250);

  beep(NOTE_G6, 250);
  beep(NOTE_E6, 200);

  beep(NOTE_GS4, 125);
  beep(NOTE_C5, 125);
  beep(NOTE_DS5, 125);
  beep(NOTE_GS5, 125);
  beep(NOTE_C6, 125);
  beep(NOTE_DS6, 250);

  beep(NOTE_GS6, 250);
  beep(NOTE_F6, 200);

  beep(NOTE_AS4, 125);
  beep(NOTE_D5, 125);
  beep(NOTE_F5, 125);
  beep(NOTE_CS6, 125);
  beep(NOTE_D6, 125);
  beep(NOTE_F6, 250);

  beep(NOTE_B6, 250);
  beep(NOTE_B6, 125);
  beep(NOTE_B6, 125);
  beep(NOTE_B6, 125);



  break;
}

}
