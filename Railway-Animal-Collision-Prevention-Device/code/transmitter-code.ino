// Define Pins
const int pirPin = 2;     // PIR Sensor Output
const int mmWavePin = 3;  // mmWave Sensor Output

bool lastState = false; // To track if we previously sent an alert

void setup() {
  // Start Hardware Serial on pins 0 (RX) and 1 (TX) at 9600 baud for the HC-12
  Serial.begin(9600); 
  
  pinMode(pirPin, INPUT);
  pinMode(mmWavePin, INPUT);
}

void loop() {
  // Read both sensors
  bool pirDetected = digitalRead(pirPin) == HIGH;
  bool mmWaveDetected = digitalRead(mmWavePin) == HIGH;
  
  // The AND logic: Both sensors must be HIGH to confirm an animal
  bool animalPresent = (pirDetected && mmWaveDetected);
  
  if (animalPresent) {
    Serial.write('A'); // Transmit 'A' for Alert directly over Hardware Serial
    delay(500);        // Send the alert twice a second while the animal is there
  } else {
    // If an animal was just there but left, send a Clear signal
    if (lastState == true) {
      Serial.write('C'); // Transmit 'C' for Clear
    }
    delay(100); // Short delay for stability
  }
  
  // Save the current state for the next loop
  lastState = animalPresent; 
}