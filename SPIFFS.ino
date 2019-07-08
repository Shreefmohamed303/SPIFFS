/********************************************************************************
 * Module : NODEMCU
 *
 * File Name : task2
 *
 * Description : - using SPIFFS to create database for analog sensor readings 
 *              
 * 
 * Author : Shreef Mohamed
 *
 * Created on: juli 8, 2019
 *
 ********************************************************************************/

#include "FS.h"

#define ANALOG_PIN A0


char sensor_readings ; 

void setup() {
  Serial.begin(9600);
  SPIFFS.begin();
  Serial.println("Please wait 30 secs for SPIFFS to be formatted");
  SPIFFS.format();
  Serial.println("Spiffs formatted");
}


void loop() {

   sensor_readings= analogRead(ANALOG_PIN) ; 
  // open file for writing
  File f = SPIFFS.open("/f.txt", "w");
  if (!f) {
      Serial.println("file open failed");
  }
  Serial.println("====== Writing to SPIFFS file =========");
  // write 10 strings to file
  for (int i=1; i<=100; i++){
    sensor_readings= analogRead(ANALOG_PIN) ;
    f.print("Sensor Reading is : ");
    f.println(sensor_readings);
    delay(200);
  }

  f.close();

  // open file for reading
  f = SPIFFS.open("/f.txt", "r");
  if (!f) {
      Serial.println("file open failed");
  }
  Serial.println("====== Reading from SPIFFS file =======");
  for (int i=1; i<=100; i++){
    String s=f.readStringUntil('\n');
  }

  // wait a few seconds before doing it all over again
  delay(3000);
  
}
