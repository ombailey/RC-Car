#include <IRremote.hpp>

const int RECV_PIN = 2;
const unsigned long forward_hex = 0xE718FF00; 
const unsigned long reverse_hex = 0xAD52FF00;
const unsigned long move_right_hex = 0xA55AFF00;
const unsigned long move_left_hex = 0xF708FF00;
const unsigned long reverse_right_hex = 0xF20DFF00;
const unsigned long reverse_left_hex = 0xE916FF00;
const unsigned long stop_hex = 0xE31CFF00;
unsigned long move_command;

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

    // If button is repeated, set receivedCode equal to the original button
    if (receivedCode == 0){
      receivedCode = move_command;
    }else {
    move_command = receivedCode;
    }
  }
  
    IrReceiver.resume(); // ready for next code

  switch(move_command) {
    case forward_hex: Forward(); break;
    case reverse_hex: Reverse(); break;
    case stop_hex: Stop(); break;
    case move_left_hex: MoveLeft(); break;
    case move_right_hex: MoveRight(); break;
    case reverse_left_hex: ReverseLeft();break;
    case reverse_right_hex: ReverseRight();break;
    }

  }

void Forward() {
  // Motor A 
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  // Motor B 
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("Forward");
}

void Reverse() {
  // Motor A
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  // Motor B
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("Reverse");
}

void MoveLeft() {
  // Motor A
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  // Motor B
  digitalWrite(IN3,LOW);
  digitalWrite(IN4, LOW);
  Serial.println("Right");
}

void MoveRight() {
  // Motor A
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  // Motor B
  digitalWrite(IN3,LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("Left");
}


void Stop(){
  // Motor A 
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  // Motor B 
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  Serial.println("Stopped");
}

void ReverseLeft(){
 // Motor A 
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  // Motor B 
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  Serial.println("Reverse Right");
}

void ReverseRight(){
 // Motor A 
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  // Motor B 
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  Serial.println("Reverse Left");
}