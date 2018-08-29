#include <Servo.h>


Servo myservo3;
int us = 980;
int state = 0;
int substate = 0;

void heartbeat();
void startMotor();

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  
  Serial.begin(57600); while(!Serial); // wartet bis Serial da ist
  
  myservo3.attach(3,1000,2000); // attaches the servo on pin 3 to the servo object
  write2servo(us);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
  
  // wait a little for the ESC to boot up
  //for (int i=0; i < 20; i++) {
  //  heartbeat();
  //  delay(100);
  //}
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("OK\n");
  while (Serial.available() <= 0) {
    heartbeat();
  }
  Serial.println("START\n");
  startMotor();
 
}

void startMotor() {
  us=1310; write2servo(us); heartbeat();
  us=1330; write2servo(us); heartbeat();
  us=1350; write2servo(us); heartbeat();
  us=1310; write2servo(us); heartbeat();
  us=1330; write2servo(us); heartbeat();
  us=1150; write2servo(us); heartbeat();
}

void write2servo(int us) {
  if (us > 900 && us < 2100) {
    myservo3.writeMicroseconds(us); 
    //Serial.println(us);
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

