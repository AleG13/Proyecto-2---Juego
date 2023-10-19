#include <esp_now.h>
#include <WiFi.h>

// Reemplaza con la dirección MAC del ESP8266 receptor
uint8_t receiverAddress[] = {0x7C,0x87, 0xCE, 0xB6, 0x72, 0xAF}; //Mac Address: 7C:87:CE:B6:72:AF

#define X_AXIS_PIN 32
#define Y_AXIS_PIN 33
#define SWITCH_PIN 25

struct PacketData
{
  byte xAxisValue;
  byte yAxisValue;
};

PacketData data;

int mapJoystick(int value, bool reverse)
{
  if (value >= 2200)
  {
    value = map(value, 2200, 4095, 127, 0);
  }
  else if (value <= 2150)
  {
    value = map(value, 2200, 0, 127, 255);  
  }
  else
  {
    value = 127;
  }

  if (reverse)
  {
    value = 254 - value;
  }
  return value;
}


void setup() {
  Serial.begin(115200);
  // Inicializa WiFi
  WiFi.mode(WIFI_STA);

  pinMode(SWITCH_PIN, INPUT_PULLUP);   
  // Inicializa ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error inicializando ESP-NOW");
    return;
  }

  // Agrega el nodo receptor
  esp_now_peer_info_t peerInfo;
  memset(&peerInfo, 0, sizeof(esp_now_peer_info_t));
  memcpy(peerInfo.peer_addr, receiverAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false; // Puedes habilitar la encriptación si es necesario

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Error agregando el nodo receptor");
    return;
  }
}

void loop() {

  data.xAxisValue = mapJoystick(analogRead(X_AXIS_PIN), false);
  data.yAxisValue = mapJoystick(analogRead(Y_AXIS_PIN), false);  

  

  // Envía los datos al nodo receptor
  esp_now_send(receiverAddress, (uint8_t *) &data, sizeof(data));

  Serial.println("Datos enviados al ESP8266");
  delay(50);
}
