// Define the pins connected to the motor driver
const int ENA = 3;                    // Enable motor A
const int IN1 = 4;                    // Motor A input 1
const int IN2 = 5;                    // Motor A input 2
const int voltageSensorPin = A0;      // Analog pin for voltage sensor
const int currentSensorPin = A1;      // Analog pin for current sensor
const int vibrationSensorPin = 8;     // Digital pin for vibration sensor
const int resetButtonPin = 7;         // Digital pin for reset button
const int temperatureSensorPin = A2;  // Analog pin for LM35D temperature sensor

volatile unsigned long pulseCount;
unsigned long lastPulseCount;
unsigned long lastMillis;

void setup() {
  // Set the motor control pins as outputs
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  
  // Set up vibration sensor
  pinMode(vibrationSensorPin, INPUT);
  
  // Set up reset button
  pinMode(resetButtonPin, INPUT_PULLUP);
  
  Serial.begin(9600); // Initialize serial communication for debugging
  
  pulseCount = 0;
  lastPulseCount = 0;
  lastMillis = millis();
}

void loop() {
  // Read vibration sensor
  int vibrationState = digitalRead(vibrationSensorPin);
  
  if (vibrationState == LOW) {
    // Vibration detected, stop the motor and wait until reset button is pressed
    digitalWrite(ENA, LOW);  // Disable motor A
    digitalWrite(IN2, LOW);
    digitalWrite(IN1, LOW);
    Serial.println("Vibration detected, stopping motor.");
    
    while (digitalRead(resetButtonPin) == HIGH) {
      // Wait until reset button is pressed
    }
    // Reset pulse count and resume motor operation
    pulseCount = 0;
  } else {
    // Read temperature sensor
    int temperature = analogRead(temperatureSensorPin);
    float voltage = temperature * (5.0 / 1023.0);
    float celsius = voltage * 100;  // LM35D outputs 10mV per degree Celsius
    Serial.print("Temperature: ");
    Serial.print(celsius);
    Serial.println(" degrees Celsius");

    // Check temperature condition
    if (celsius >= 150) { // Adjust threshold temperature as needed
      // Overheating detected, stop the motor and wait until reset button is pressed
      digitalWrite(ENA, LOW);  // Disable motor A
      digitalWrite(IN2, LOW);
    digitalWrite(IN1, LOW);
      Serial.println("Overheating detected, stopping motor.");

      while (digitalRead(resetButtonPin) == HIGH) {
        // Wait until reset button is pressed
      }
      // Reset pulse count and resume motor operation
      pulseCount = 0;
    } else {
      // Read current sensor
      float current = ((analogRead(currentSensorPin) - 512) * (5.0 / 1023.0) / 0.185)+0.1; // Convert analog reading to current (in Amperes)
      Serial.print("Current: ");
      Serial.print(current);
      Serial.println(" A");
      
      // Check current condition
      if (current >= 30) { // Adjust threshold current as needed
        // Excessive current detected, stop the motor and wait until reset button is pressed
        digitalWrite(ENA, LOW);  // Disable motor A
        digitalWrite(IN2, LOW);
    digitalWrite(IN1, LOW);
        Serial.println("Excessive current detected, stopping motor.");

        while (digitalRead(resetButtonPin) == HIGH) {
          // Wait until reset button is pressed
        }
        // Reset pulse count and resume motor operation
        pulseCount = 0;
      } else {
        // No overheating or excessive current detected, rotate motor in one direction at full speed
        digitalWrite(ENA, HIGH);  // Enable motor A
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);

        // Read and print voltage
        float voltage = (analogRead(voltageSensorPin) * (5.0 / 1023.0) * (25.0 / 5.0))+10; // Convert analog reading to voltage
        Serial.print("Voltage: ");
        Serial.print(voltage);
        Serial.println(" V");

        // Calculate RPM
        unsigned long currentTime = millis();
        unsigned long elapsedTime = currentTime - lastMillis;
        if (elapsedTime >= 1000) {  // Calculate RPM every second
          unsigned long pulseDifference = pulseCount - lastPulseCount;
          float rpm = (pulseDifference / 20.0) * (60000.0 / elapsedTime); // 20 slots on the encoder wheel
          Serial.print("RPM: ");
          Serial.println(rpm);
          lastPulseCount = pulseCount;
          lastMillis = currentTime;
        }
      }
    }
  }

  delay(1000); // Wait for 1 second
}
