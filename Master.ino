// Liblaries:
#include <Servo.h>
#include <IRremote.h>

Servo wlacznik;


// Pins:
int buttonPin = 2;
int servoPin = 9;
int irPin = 11;
int servoSwitch = 10;

// Need to work:
boolean switchNow = false; // button press = true
boolean switchPrev = false;


// Servo positions:
int lastPos = 105;
int ON = 47;
int MIDDLE = 78;
int OFF = 105;

decode_results irRes;
IRrecv irrecv(irPin);

void setup()
  {
    // Servo 
    wlacznik.attach(servoPin); // Attachin servo to Arduino
    wlacznik.write(MIDDLE); // Setting servo to middle position
    
    irrecv.enableIRIn(); // IR
    
    pinMode(buttonPin, INPUT_PULLUP);  // button 
  }


void loop()
  {
    switchNow = digitalRead(buttonPin);
    
    if (switchNow == false && switchPrev != switchNow)
      {
        switchPrev = switchNow;
        lamp();
        delay(2000);
      }
    
    if (switchNow == true)
        switchPrev = true;
    
    if (irrecv.decode(&irRes))
      {
        switch (irRes.value)
          {
             case 0x4FFF00F:
               lamp();
               delay(2000);
               break;
          }
         irrecv.resume();
      }
  }        
              
        
void lamp()
  {
    if (lastPos == OFF)
      {
        digitalWrite(servoSwitch, HIGH);
        delay(150);
        wlacznik.write(ON);
        delay(150);
        wlacznik.write(MIDDLE);
        wlacznik.write(ON);
        delay(150);
        wlacznik.write(MIDDLE);
        delay(150);
        lastPos = ON;
        digitalWrite(servoSwitch, LOW);
      }
     else
      {
        digitalWrite(servoSwitch, HIGH);
        delay(150);
        wlacznik.write(OFF);
        delay(150);
        wlacznik.write(MIDDLE);
        wlacznik.write(OFF);
        delay(150);
        wlacznik.write(MIDDLE);
        delay(150);
        lastPos = OFF;
        digitalWrite(servoSwitch, LOW);
      }
   }
