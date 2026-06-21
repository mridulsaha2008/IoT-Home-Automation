#define relay 5

void setup() {
  Serial.begin(9600); // Initialize hardware serial interface
  pinMode(relay, OUTPUT);
  digitalWrite(relay, HIGH); // Keeping active-low relay safely OFF at startup
}

void loop() {
  if (Serial.available() > 0) {
    // Read the string until a newline or carriage return character is parsed
    String command = Serial.readStringUntil('\n');
    command.trim(); // Sanitizes white spaces or hidden carriage returns (\r)

    if (command == "turn on") {
      digitalWrite(relay, LOW);   // Relay ON (Low-level active trigger)
    } else if (command == "turn off") {
      digitalWrite(relay, HIGH);  // Relay OFF
    }
  }
}
