#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

const int UP_LED = 25;
const int DOWN_LED = 26;
const int LEFT_LED = 27;
const int RIGHT_LED = 14;

void setup() {

  Serial.begin(115200);

  SerialBT.begin("ESP32_JOYSTICK");

  // Setup PWM channels
  ledcSetup(0, 5000, 8);
  ledcSetup(1, 5000, 8);
  ledcSetup(2, 5000, 8);
  ledcSetup(3, 5000, 8);

  // Attach pins
  ledcAttachPin(UP_LED, 0);
  ledcAttachPin(DOWN_LED, 1);
  ledcAttachPin(LEFT_LED, 2);
  ledcAttachPin(RIGHT_LED, 3);

  Serial.println("Ready");
}

void loop() {

  if (SerialBT.available()) {

    String cmd = SerialBT.readStringUntil('\n');

    cmd.trim();

    int value = constrain(
      cmd.substring(1).toInt(),
      0,
      255
    );

    ledcWrite(0,0);
    ledcWrite(1,0);
    ledcWrite(2,0);
    ledcWrite(3,0);

    switch(cmd.charAt(0)) {

      case 'U':
        ledcWrite(0,value);
        break;

      case 'D':
        ledcWrite(1,value);
        break;

      case 'L':
        ledcWrite(2,value);
        break;

      case 'R':
        ledcWrite(3,value);
        break;
    }
  }
}