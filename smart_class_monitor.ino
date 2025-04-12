#include <DHT.h>
#include <DHT_U.h>

// Pin definitions
#define TRIG_PIN 9
#define ECHO_PIN 10
#define DHTPIN 2
#define BUZZER_PIN 8

// Sensor types
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Variables
long duration;
float distance;
float temperature;

void setup() {
  Serial.begin(9600);
  dht.begin();

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  // --- Read Ultrasonic Distance ---
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration * 0.034 / 2;

  // --- Read Temperature from DHT11 ---
  temperature = dht.readTemperature();

  if (isnan(temperature)) {
    Serial.println("Failed to read from DHT11!");
    return;
  }

  // --- Debug output ---
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm | Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  // --- Check both conditions ---
  if (distance < 100 && temperature > 10) {
    digitalWrite(BUZZER_PIN, HIGH);  // Buzzer ON
  } else {
    digitalWrite(BUZZER_PIN, LOW);   // Buzzer OFF
  }

  delay(1000);  // Optional delay
}
