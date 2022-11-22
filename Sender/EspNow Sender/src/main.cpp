#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
 
typedef struct message {
  float temperature;
  float humidity;
};
 
struct message myMessage;
 
void onDataReceiver(const uint8_t * mac, const uint8_t *incomingData, int len) {
  Serial.println("Message received.");
 // Não usamos mac para verificar o remetente
 // Vamos transformar os dados recebidos em nossa estrutura de mensagem
 memcpy(&myMessage, incomingData, sizeof(myMessage));
 Serial.println("=== Data ===");
 Serial.print("endereço MAC: ");
 for (int i = 0; i < 6; i++) {
     Serial.print("0x");
     Serial.print(mac[i], HEX);
     Serial.print(":");
 }
    
 Serial.print("\n\nTemperatura: ");
 Serial.println(myMessage.temperature);
 Serial.print("\nUmidade: ");
 Serial.println(myMessage.humidity);
 Serial.println();
}
 
void setup() {
 Serial.begin(115200);
 WiFi.mode(WIFI_STA);
 
 // Obter Mac Add
 Serial.print("Endereço MAC:");
 Serial.print(WiFi.macAddress());
 Serial.println("ESP32 ESP-Now Broadcast");
 
 // Inicializando o ESP-NOW
 if (esp_now_init() != 0) {
   Serial.println("Problema durante a inicialização ESP-NOW");
   return;
 }
 esp_now_register_recv_cb(onDataReceiver);
}
 
void loop() {
 // coloque seu código principal aqui, para executar repetidamente:
}