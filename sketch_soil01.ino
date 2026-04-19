// Soil Health & Disease Warning System

// Pin Definitions
const int soilPin = A0;
const int tempPin = A1;
const int gasPin  = A2;

const int relayPin = 9;   
const int ledPin   = 7;
const int buzzerPin = 8;

// Thresholds
int moistureThreshold = 400;
int gasThreshold = 300;

void setup() {
  Serial.begin(9600);

  pinMode(relayPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  digitalWrite(relayPin, LOW);
  digitalWrite(ledPin, LOW);
  digitalWrite(buzzerPin, LOW);
}

void loop() {

  int moistureValue = analogRead(soilPin);
  int gasValue = analogRead(gasPin);

  int tempRaw = analogRead(tempPin);
  float voltage = tempRaw * (5.0 / 1023.0);
  float temperature = (voltage - 0.5) * 100;

  Serial.print("Moisture: ");
  Serial.print(moistureValue);
  Serial.print(" | Gas: ");
  Serial.print(gasValue);
  Serial.print(" | Temp: ");
  Serial.println(temperature);

  if (moistureValue < moistureThreshold) {
    digitalWrite(relayPin, HIGH);
    digitalWrite(ledPin, HIGH);
    digitalWrite(buzzerPin, HIGH);

    Serial.println("Soil Dry → Pump ON");

  } else {
    digitalWrite(relayPin, LOW);

    if (gasValue > gasThreshold) {
      digitalWrite(ledPin, HIGH);
      digitalWrite(buzzerPin, HIGH);

      Serial.println("Gas High → Disease Risk!");
    } else {
      digitalWrite(ledPin, LOW);
      digitalWrite(buzzerPin, LOW);

      Serial.println("Soil Healthy");
    }
  }

  delay(2000);
}