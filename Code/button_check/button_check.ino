#include <IRremote.hpp>  // Note the different include!

const int RECV_PIN = 2; // IR receiver signal pin

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(RECV_PIN, ENABLE_LED_FEEDBACK); // Init the receiver
  Serial.println("IR Receiver Initialized.");
}

void loop() {
  if (IrReceiver.decode()) {
    Serial.print("Received IR code: ");
    Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX); // Only command, not raw
    IrReceiver.resume(); // Prepare to receive the next value
  }
}
