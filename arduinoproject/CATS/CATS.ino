#include <Arduino.h>
#include "Buzzer.h"
#include "Bluetooth.h"
#include "Button.h"

Buzzer buzzer;
Bluetooth bluetooth;
Button buzzerButton(5);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  
}

void loop() {
  // put your main code here, to run repeatedly:
  if(buzzerButton == LOW){
    buzzer.on();
    buzzer.off();
  }
}
