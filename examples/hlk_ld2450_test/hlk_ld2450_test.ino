#include "HLK_LD2450.h"

/*#define ld2450_rx 14
#define ld2450_tx 27

SoftwareSerial ld2450_ss(ld2450_rx, ld2450_tx);*/

#define hlk_ld2450_ser Serial1
//#define hlk_ld2450_ser ld2450_ss

HLK_LD2450 ld2450(&hlk_ld2450_ser);

void setup() {
  Serial.begin(115200);
  hlk_ld2450_ser.begin(115200);
  //ld2450.begin();
}

void loop() {

  ld2450.read();
  
  Serial.print("Target X: ");
  Serial.println(ld2450.getTargetX());
  Serial.print("Target Y: ");
  Serial.println(ld2450.getTargetY());
  Serial.print("Speed: ");
  Serial.println(ld2450.getSpeed());
  Serial.print("tDisRes: ");
  Serial.println(ld2450.getDistanceResolution());
  Serial.println("-----------------------------------------------");
}
