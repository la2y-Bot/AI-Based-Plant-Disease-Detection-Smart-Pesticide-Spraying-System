#include <WiFi.h>
#include <HTTPClient.h>
#include <AccelStepper.h>

// ======= WiFi Credentials =======
const char* ssid = "aditya";
const char* password = "aditya12";

// ======= Firebase URLs =======
String firebaseCamURL = "https://picamcontrol-default-rtdb.firebaseio.com/cameraCommand.json";
String firebaseScanURL = "https://picamcontrol-default-rtdb.firebaseio.com/scanCommand.json";

// ======= Stepper Motors =======
AccelStepper motor2(AccelStepper::FULL4WIRE, 18, 21, 19, 22);  // Motor 2
AccelStepper motor3(AccelStepper::FULL4WIRE, 23, 14, 13, 27);  // Motor 3

const int forwardSteps = 8192;
const int backwardSteps = 7800;

// ======= Setup =======
void setup() {
  Serial.begin(115200);

  // Motor setup
  motor2.setMaxSpeed(300);
  motor2.setAcceleration(200);
  motor3.setMaxSpeed(300);
  motor3.setAcceleration(200);

  // WiFi connection
  WiFi.begin(ssid, password);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println("\n✅ WiFi Connected!");
}

// ======= Firebase Helpers =======
void setFirebaseValue(String url, String value) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(url);
    http.addHeader("Content-Type", "application/json");
    String payload = "{\"value\":\"" + value + "\"}";
    int code = http.PATCH(payload);
    http.end();
    Serial.println("📡 Updated " + url + " to: " + value);
  }
}

String getFirebaseValue(String url) {
  HTTPClient http;
  http.begin(url);
  int code = http.GET();
  String result = http.getString();
  http.end();

  int s = result.indexOf(":");
  int e = result.indexOf("}");
  String val = result.substring(s + 2, e - 1);
  return val;
}

// ======= Stepper Functions =======
void moveForward() {
  Serial.println("🚀 Moving Forward...");
  motor2.move(-forwardSteps);  // Motor 2 anticlockwise
  motor3.move(+forwardSteps);  // Motor 3 clockwise
  while (motor2.distanceToGo() != 0 || motor3.distanceToGo() != 0) {
    motor2.run();
    motor3.run();
  }
  Serial.println("✅ Reached Target Position (Forward)");
}

void moveBackward() {
  Serial.println("⬅ Moving Backward...");
  motor2.move(+backwardSteps);  // Motor 2 clockwise
  motor3.move(-backwardSteps);  // Motor 3 anticlockwise
  while (motor2.distanceToGo() != 0 || motor3.distanceToGo() != 0) {
    motor2.run();
    motor3.run();
  }
  Serial.println("✅ Returned to Initial Position");
}

// ======= Main Loop =======
void loop() {
  String scanVal = getFirebaseValue(firebaseScanURL);
  Serial.println("📥 Scan command: " + scanVal);

  if (scanVal == "scan") {
    Serial.println("🔹 Scan triggered from website");

    // Step 1: Move motors forward
    moveForward();

    // Step 2: Tell Pi to take a picture
    setFirebaseValue(firebaseCamURL, "click");

    // Step 3: Wait for Pi to complete the task
    while (true) {
      String camVal = getFirebaseValue(firebaseCamURL);
      Serial.println("📸 Camera status: " + camVal);

      if (camVal == "done" || camVal == "idle") {
        Serial.println("✅ Pi finished scanning!");

        // Step 4: Reset Firebase commands
        setFirebaseValue(firebaseScanURL, "idle");
        setFirebaseValue(firebaseCamURL, "idle");

        // Step 5: Move motors backward
        moveBackward();
        break;
      }

      delay(500);
    }
  }

  delay(1000); // check every second
}