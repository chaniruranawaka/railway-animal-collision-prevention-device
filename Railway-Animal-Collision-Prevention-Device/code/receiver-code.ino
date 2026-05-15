// Define Pins
const int buzzerPin = 8; // Buzzer Positive Pin

unsigned long lastAlertTime = 0;
const unsigned long timeoutMillis = 2000; // 2 seconds timeout

void setup() {
  // Start Hardware Serial on pins 0 (RX) and 1 (TX) at 9600 baud for the HC-12
  Serial.begin(9600); 
  
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW); // Ensure buzzer is off at startup
}

void loop() {
  // Check if a message is arriving directly from the HC-12 on Hardware RX (Pin 0)
  if (Serial.available()) {
    char incomingSignal = Serial.read();
    
    if (incomingSignal == 'A') {
      digitalWrite(buzzerPin, HIGH); // Turn on buzzer
      lastAlertTime = millis();      // Reset the failsafe timer
    } 
    else if (incomingSignal == 'C') {
      digitalWrite(buzzerPin, LOW);  // Turn off buzzer
    }
  }
  
  // Failsafe Timeout Logic
  // If the buzzer is ON, but we haven't received an 'A' in 2 seconds, turn it off.
  if (digitalRead(buzzerPin) == HIGH) {
    if (millis() - lastAlertTime > timeoutMillis) {
      digitalWrite(buzzerPin, LOW);
    }
  }
}