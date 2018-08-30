#include <Servo.h>

// output pin that controls the ESC
#define SERVOPIN 3

// idle speed of motor 
#define IDLESPEED 1100

// input to switch motor to low speed (active low)
#define LOWSPEED_PIN 4
#define LOWSPEED 1150

// input pin to switch motor to high speed (active low)
#define HIGHSPEED_PIN 5
#define HIGHSPEED 1250

// input pin to switch on the high voltage (active low)
#define HIGH_V_PIN 6

// define this if you want something that uses Serial and waits for signal on Serial to start
// #define DEBUG

Servo myservo3;
int us = 980;
int state = 0;
int substate = 0;

void heartbeat();
void startMotor();

void setup() {
  // configure all pins:
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LOWSPEED_PIN, INPUT_PULLUP);
  pinMode(HIGHSPEED_PIN, INPUT_PULLUP);
  pinMode(HIGH_V_PIN, INPUT_PULLUP);
  // show we are done:
  digitalWrite(LED_BUILTIN, HIGH);

  #ifdef DEBUG
  Serial.begin(57600); while(!Serial); // wartet bis Serial da ist
  #endif

  // configure ESC and write initial value (980), then wait a second for the ESC to see the PWM
  myservo3.attach(SERVOPIN,1000,2000); // attaches the servo on pin 3 to the servo object
  write2servo(us);
  delay(3000);

  // tell the user we are done with setup:
  digitalWrite(LED_BUILTIN, LOW);


 #ifdef DEBUG
  Serial.println("OK\n");
  while (Serial.available() <= 0) {
    heartbeat();
  }
  Serial.println("START\n");
  startMotor();
  #endif
 
}

void startMotor() {
  us=1310; write2servo(us); heartbeat();
  us=1330; write2servo(us); heartbeat();
  us=1350; write2servo(us); heartbeat();
  us=1310; write2servo(us); heartbeat();
  us=1330; write2servo(us); heartbeat();
  us=IDLESPEED; write2servo(us); heartbeat();
}

void write2servo(int us) {
  if (us > 900 && us < 2100) {
    myservo3.writeMicroseconds(us); 
    #ifdef DEBUG
    Serial.println(us);
    #endif
  }
}


void loop() {
  //
  // show we are alive
  heartbeat();
  us--;
  write2servo(us);
  
#ifdef UNDEFINED
  switch(state) {
    case 0: us = 1310; write2servo(us); state=1; substate=0; break;
    case 1: {
      heartbeat();
      substate++; 
      if (substate & 1) { us = us + 10; }
      write2servo(us);
      if ((substate & 15) == 8) { us = us - 40; }
      if (substate > 30) state = 2;
    }
    break;
    case 2: {
      us = 1250;
      write2servo(us);
      substate = 3;
    }
    break;
  default:
    state = 0;
    // retry for ever...            
  }
#endif

  //startMotor();
  
  // OK, we are done, wait
  delay(500);
}



// flickers the LED briefly. Takes 100 milliseconds.
void heartbeat() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(25);
  digitalWrite(LED_BUILTIN, LOW);
  delay(75);
}

