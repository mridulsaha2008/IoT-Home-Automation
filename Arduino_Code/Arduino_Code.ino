#define relay 5

void setup() {
  Serial.begin(9600);
  pinMode(relay, OUTPUT);
  digitalWrite(relay, HIGH);
}

void loop() {
  String command = Serial.readStringUntil('\r');

  if (command == "turn on") {
    digitalWrite(relay, LOW);
  } else if (command == "turn off") {
    digitalWrite(relay, HIGH);
  }
}
