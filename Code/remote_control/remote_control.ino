#include <IRremote.hpp>

const int RECV_PIN = 2;
const unsigned long FORWARD_CODE = 0xE718FF00; // <-- Your forward button hex code

// Motor control pins
const int IN1 = 9;
const int IN2 = 8;
const int IN3 = 7;
const int IN4 = 6;

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(RECV_PIN, ENABLE_LED_FEEDBACK);
  Serial.println("IR Receiver Initialized.");

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop() {
  if (IrReceiver.decode()) {
    unsigned long receivedCode = IrReceiver.decodedIRData.decodedRawData;
    Serial.print("Received IR code: ");
    Serial.println(receivedCode, HEX);

    if (receivedCode == FORWARD_CODE) {
      moveForward();
    }

    IrReceiver.resume(); // Prepare for next code
  }
}

void moveForward() {
  // Motor A 
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  // Motor B 
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  Serial.println("Moving Forward");
}

void Stop(){
  // Motor A 
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  // Motor B forward
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  Serial.println("Stopped");
}
}