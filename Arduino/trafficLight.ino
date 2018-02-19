#include "TrafficLight.hpp"

TrafficLight::Manager manager;

int nextDelay = 0;
uint8_t byteRead = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  
  if( Serial.available() > 0 ) {
    
    byteRead = Serial.read();
    Serial.println(byteRead);

    if( byteRead == 'A' ) {
      manager.switchMode();
    }
  } else {
    Serial.println("-");
  }

  // Step the manager and step delay
  nextDelay = manager.step();
  
  // Wait and update
  delay(nextDelay);
  
}
