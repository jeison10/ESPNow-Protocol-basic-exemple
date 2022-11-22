/**
* ESP-NOW
*
* Sender
*/
 
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <espnow.h>
#include <SPI.h>
#include <Wire.h>

 

 
uint8_t peer1[] = {0xF0, 0x08, 0xD1, 0xD2, 0x91, 0xF4}; //F0:08:D1:D2:91:F4
 
  struct message {
  float temperature;
  float humidity;
};
 
struct message myMessage;
 

 
void onSent(uint8_t *mac_addr, uint8_t sendStatus) {
 Serial.println("Status:");
 Serial.println(sendStatus);
}
 
void setup() {
 Serial.begin(115200);
 
 
 WiFi.mode(WIFI_STA);
 
 // Obter Mac Add
 Serial.print("Endereço MAC:");
 Serial.print(WiFi.macAddress());
 Serial.println("ESP-Now Sender");

 // Inicializando o ESP-NOW
 if (esp_now_init() != 0) {
   Serial.println("Problema durante a inicialização ESP-NOW");
   return;
 }
 
 esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
 // Registre o par
 Serial.println("Registrando um par");
 esp_now_add_peer(peer1, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
 Serial.println("Registrando a função de retorno de chamada");
 esp_now_register_send_cb(onSent);
}
 
void loop() {
 myMessage.temperature = random(0,255);
 myMessage.humidity = random(0,255);
 
 Serial.println("Envie uma nova mensagem");
 esp_now_send(NULL, (uint8_t *) &myMessage, sizeof(myMessage));
 
 delay(2000);
}