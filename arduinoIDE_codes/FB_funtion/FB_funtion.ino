#include <AccelStepper.h>

// Define motors
AccelStepper motor2(AccelStepper::FULL4WIRE, 18, 21, 19, 22);  // Motor 2
AccelStepper motor3(AccelStepper::FULL4WIRE, 23, 14, 13, 27);  // Motor 3

const int forwardSteps = 8192;
const int backwardSteps = 7800;

void setup() {
  Serial.begin(115200);

  motor2.setMaxSpeed(300);
  motor2.setAcceleration(200);

  motor3.setMaxSpeed(300);
  motor3.setAcceleration(200);

  Serial.println("Type 'F' to move forward 8192 steps");
  Serial.println("Type 'B' to move backward 7800 steps");
}

void loop() {
  if (Serial.available()) {
    char cmd = Serial.read();
    if (cmd == 'F' || cmd == 'f') {
      moveForward();
    } else if (cmd == 'B' || cmd == 'b') {
      moveBackward();
    } else {
      Serial.println("Invalid command. Use F or B");
    }
  }

  motor2.run();
  motor3.run();
}

void moveForward() {
  Serial.println("Moving forward 8192 steps");

  motor2.move(-forwardSteps);  // Motor 2 anticlockwise
  motor3.move(+forwardSteps);  // Motor 3 clockwise

  while (motor2.distanceToGo() != 0 || motor3.distanceToGo() != 0) {
    motor2.run();
    motor3.run();
  }
}

void moveBackward() {
  Serial.println("Moving backward 7800 steps");

  motor2.move(+backwardSteps);  // Motor 2 clockwise
  motor3.move(-backwardSteps);  // Motor 3 anticlockwise

  while (motor2.distanceToGo() != 0 || motor3.distanceToGo() != 0) {
    motor2.run();
    motor3.run();
  }
}