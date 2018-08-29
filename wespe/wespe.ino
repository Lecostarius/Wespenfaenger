void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);

}

void loop() {
  // check for inputs:
  //
  // show we are alive
  heartbeat();

  // OK, we are done, wait
  delay(500);
}

// flickers the LED briefly
void heartbeat() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);
  delay(100);
}

