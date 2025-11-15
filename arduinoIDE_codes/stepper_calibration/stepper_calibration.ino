#include <AccelStepper.h>

// Define motors with correct pin order: IN1, IN3, IN2, IN4
AccelStepper motor1(AccelStepper::FULL4WIRE, 4, 17, 16, 5);
AccelStepper motor2(AccelStepper::FULL4WIRE, 18, 21, 19, 22);
AccelStepper motor3(AccelStepper::FULL4WIRE, 23, 14, 13, 27);
AccelStepper motor4(AccelStepper::FULL4WIRE, 26, 33, 25, 32);

String input = "";
int speedLimit = 300;

void setup() {
  Serial.begin(115200);

  motor1.setMaxSpeed(speedLimit);
  motor2.setMaxSpeed(speedLimit);
  motor3.setMaxSpeed(speedLimit);
  motor4.setMaxSpeed(speedLimit);

  Serial.println("Calibration Ready. Use commands like: M1 CW, M2 CCW, M3 STOP");
}

void loop() {
  if (Serial.available()) {
    input = Serial.readStringUntil('\n');
    input.trim();
    parseCommand(input);
  }

  motor1.runSpeed();
  motor2.runSpeed();
  motor3.runSpeed();
  motor4.runSpeed();
}

void parseCommand(String cmd) {
  cmd.toUpperCase();

  if (cmd.startsWith("M1")) {
    setMotorDirection(motor1, cmd.substring(3));
  } else if (cmd.startsWith("M2")) {
    setMotorDirection(motor2, cmd.substring(3));
  } else if (cmd.startsWith("M3")) {
    setMotorDirection(motor3, cmd.substring(3));
  } else if (cmd.startsWith("M4")) {
    setMotorDirection(motor4, cmd.substring(3));
  } else {
    Serial.println("Invalid command. Use M1–M4 with CW, CCW, or STOP");
  }
}

void setMotorDirection(AccelStepper &motor, String dir) {
  if (dir == "CW") {
    motor.setSpeed(speedLimit);
    Serial.println("Motor set to clockwise");
  } else if (dir == "CCW") {
    motor.setSpeed(-speedLimit);
    Serial.println("Motor set to anticlockwise");
  } else if (dir == "STOP") {
    motor.setSpeed(0);
    Serial.println("Motor stopped");
  } else {
    Serial.println("Unknown direction. Use CW, CCW, or STOP");
  }
}