//#include <SoftwareSerial.h>
#include "HLK_LD2450.h"

#define ld2450_rx 14
#define ld2450_tx 27

HLK_LD2450 ld2450(ld2450_rx, ld2450_tx, &Serial1);
//HLK_LD2450 ld2450(&Serial2);

void setup() {
  Serial.begin(115200);
  ld2450.begin();
}

void loop() {

  ld2450.read();

  int16_t x_coordinate = ld2450.getTargetX();
  int16_t y_coordinate = ld2450.getTargetY();
  int16_t speed = ld2450.getSpeed();
  uint16_t distance_resolution = ld2450.getDistanceResolution();

  Serial.print("X Coordinate: ");
  Serial.println(x_coordinate);
  Serial.print("Y Coordinate: ");
  Serial.println(y_coordinate);
  Serial.print("Speed: ");
  Serial.println(speed);
  Serial.print("Distance Resolution: ");
  Serial.println(distance_resolution);
  Serial.println("-----------------------------------------------");
}
