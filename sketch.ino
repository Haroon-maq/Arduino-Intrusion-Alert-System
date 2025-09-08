
const int ledPin = 12;
char buffer[10]; 
int bufferIndex = 0;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  Serial.println("Arduino ready");
}

void loop() {
  if (Serial.available() > 0) {
    char c = Serial.read();
    if (c == '\n' || bufferIndex >= sizeof(buffer) - 1) {
      buffer[bufferIndex] = '\0';
      Serial.print("Received message: [");
      Serial.print(buffer);
      Serial.println("]");
      
      if (strcmp(buffer, "ALERT") == 0) {
        Serial.println("ALERT command received! Blinking LED...");
        for (int i = 0; i < 3; i++) {
          digitalWrite(ledPin, HIGH);
          delay(300);
          digitalWrite(ledPin, LOW);
          delay(300);
        }
        Serial.println("Done blinking");
      } else {
        Serial.println("No ALERT command.");
      }
      bufferIndex = 0; 
    } else {
      buffer[bufferIndex++] = c;
    }
  }
}
