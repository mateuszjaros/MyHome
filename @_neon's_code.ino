#include <Servo.h>
#include <IRremote.h>

// Pins:
int buttonPin = 2;
int irPin = 11;
int servoPin = 9;

// Objects:
Servo servo;
IRrecv irrecv(irPin);

// States:
boolean buttonState = false;
boolean lastButtonState = false;
boolean switchState = false; // false - down, true - up
const int switchUp = 47;
const int switchMiddle = 74;
const int switchDown = 105;

// Other:
decode_results irRes;

void setup() {
  servo.attach(servoPin);
  servo.write(switchMiddle);
  irrecv.enableIRIn();
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  lastButtonState = buttonState;
  buttonState = digitalRead(buttonPin);
  
  // Button checking
  if (!buttonState && buttonState != lastButtonState) {
    switchState = ~switchState;
  }
  // IR checking
  else if (irrecv.decode(&irRes)) {
    switch (irRes.value) {
      case 0x4FFF00F:
        switchState = ~switchState;
        break;
    }
    irrecv.resume();
  }
  
  // Changing servo position
  if (switchState) {
    servo.write(switchUp);
    delay(250);
    servo.write(switchMiddle);
  }
  else {
    servo.write(switchDown);
    delay(250);
    servo.write(switchMiddle);
  }
  
  // Delay for button debouncing.
  delay(15);
}
