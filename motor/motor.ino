#include"TrollBot.h"

TrollBot Motor(01,050);     // Initiate this node with address 01 and channel 100

void setup() {
  Motor.setup();            // Run the setup functions for this node
}

void loop() {
  Loop();                 // Run the loop function for this node
}

