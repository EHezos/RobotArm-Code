#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver srituhobby = Adafruit_PWMServoDriver();

#define servoBase 0
#define servoElbow1 1
#define servoElbow2 2
#define servoRoller 3
#define servoHand1 4
#define servoHand2 5
#define servoClaw 6

void setup() {
  Serial.begin(9600);
  srituhobby.begin();
  srituhobby.setPWMFreq(60);

  // Initial positions
  srituhobby.setPWM(servoBase, 0, 246);  // 0 degrees
  srituhobby.setPWM(servoElbow1, 0, 246);  // Initial position for elbow1
  srituhobby.setPWM(servoElbow2, 0, 246);  // Initial position for elbow2
  srituhobby.setPWM(servoRoller, 0, 410);
  srituhobby.setPWM(servoHand1, 0, 0);
  srituhobby.setPWM(servoHand2, 0, 0);
  srituhobby.setPWM(servoClaw, 0, 246); // Initial position for claw
  
  delay(3000);
}

void loop() {
  // Step 1: Move elbow1 down and close the claw
  Serial.println("Moving elbow1 down and opening the claw");
  for (int pos = 246; pos <= 400; pos++) {
    srituhobby.setPWM(servoElbow1, 0, pos); 
    srituhobby.setPWM(servoClaw, 0, 465); // close the claw
    delay(10);
  }
  delay(500); // Wait for a moment

  // Step 2: Rotate the base to the other side while elbow1 is rising back
  Serial.println("Rising elbow1 and rotating base to the other side");
  for (int pos = 246; pos <= 492; pos++) {
    srituhobby.setPWM(servoBase, 0, pos);
    delay(10);
  }
  delay(500); // Wait for a moment

  // Step 3: Move elbow1 down and open the claw to release the item
  Serial.println("Moving elbow1 down and opening the claw");
    for (int pos = 400; pos >= 246; pos--) {
    srituhobby.setPWM(servoElbow1, 0, pos); 
    delay(10);
  }
  for (int pos = 246; pos <= 400; pos++) {
    srituhobby.setPWM(servoClaw, 0, 256); // Open the claw
    delay(10);
  }

  // Step 5: rotate base back to the initial position
  Serial.println("Moving elbow1 up and rotating base back to the initial position");
  for (int pos = 492; pos >= 246; pos--) {
    srituhobby.setPWM(servoBase, 0, pos);
    delay(10);
  }
  delay(500); // Wait for a moment

  // Repeat the process
}
