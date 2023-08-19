#include <Arduino.h>
#include <string.h>
#include <ros.h>
#include <std_msgs/String.h>
#include <SPI.h>
#include <LoRa.h>

//Connections on Arduino Uno - 
// VCC - 3.3V, GND - GND
// CSN - CSN_PIN, CE - CE_PIN
// SCK - 13, MOSI - 11, MISO - 12

#define CSN_PIN 7
#define CE_PIN 8

void KeyboardInputs_cb(const std_msgs::String& keyPress);
void LoRa_Init();

ros::NodeHandle nh;
ros::Subscriber<std_msgs::String> sub("KeyboardInputs", &KeyboardInputs_cb);

void setup() {
  nh.initNode();
  nh.subscribe(sub);
  LoRa_Init();
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if(packetSize){
    nh.loginfo("Received Data");
    String data = "";
    char Data[100];
    while(LoRa.available()){
      data += (char)LoRa.read();
    }
    strcpy(Data, data.c_str());
    nh.loginfo(Data);
  }
  nh.spinOnce();
}

void KeyboardInputs_cb(const std_msgs::String& keyPress){
  String keypress = keyPress.data;
  char command[32];
  strcpy(command, keypress.c_str());
  LoRa.beginPacket();
  LoRa.print(command);
  LoRa.endPacket();
  nh.loginfo(command);
}

void LoRa_Init(){
  if(LoRa.begin(433E6)){
    Serial.println("LoRa Initialization Successful");
  }
  else{
    Serial.println("LoRa Initialization Failed");
    while(1);
  }
  LoRa.setTxPower(20);
}