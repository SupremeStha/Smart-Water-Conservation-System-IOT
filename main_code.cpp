#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int SOIL_SENSOR = A3;
const int TMP36_PIN = A1;
const int MOTOR_PIN = 5;
const int MOTOR2_PIN = 12;
const int GREEN_LED = 6;
const int YELLOW_LED = 7;
const int RED_LED = 8;
const int BUZZER = 9;
const int TRIG_PIN = 10;
const int ECHO_PIN = 11;
const int LIGHT_SENSOR = A0;

LiquidCrystal_I2C lcd(0x20, 16, 2);

void setup() {
  Serial.begin(9600);
  pinMode(SOIL_SENSOR, INPUT);
  pinMode(TMP36_PIN, INPUT);
  pinMode(MOTOR_PIN, OUTPUT);
  pinMode(MOTOR2_PIN, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LIGHT_SENSOR, INPUT);

  lcd.init();
  lcd.backlight();
  lcd.print("Starting...");
  delay(1000);
  lcd.clear();
}

void loop() {
  int soilValue = analogRead(SOIL_SENSOR);
  int moisturePercent = map(soilValue, 1023, 0, 116, 0);

  int tmpValue = analogRead(TMP36_PIN);
  float voltage = (tmpValue / 1023.0) * 5000;
  float temperatureC = (voltage - 500) / 10.0;

  long duration, distance;
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration * 0.034 / 2;

  int lightValue = analogRead(LIGHT_SENSOR);
  int lightPercent = map(lightValue, 0, 1023, -5, 106);

  bool lowWater = (distance > 200);

  lcd.setCursor(0, 0);
  lcd.print("Soil:");
  lcd.print(moisturePercent);
  lcd.print("%");
  delay(1000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp:");
  lcd.print(temperatureC, 1);
  lcd.print("C");
  delay(1000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Light:");
  lcd.print(lightPercent);
  lcd.print("%");

  lcd.setCursor(0, 1);
  if (lowWater) {
    lcd.print("Low Water!");
  } else {
    lcd.print("Water OK!");
  }
  delay(1000);

  Serial.print("Soil Moisture: ");
  Serial.print(moisturePercent);
  Serial.print("%, Temperature: ");
  Serial.print(temperatureC);
  Serial.print("C, Light: ");
  Serial.print(lightValue);
  Serial.print(" (");
  Serial.print(lightPercent);
  Serial.println("%)");
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(1000);
  
  int motorSpeed;
  if (temperatureC <= 10.0) {
      motorSpeed = 55;
  } else if (temperatureC > 10.0 && temperatureC <= 30.0) {
      motorSpeed = map(temperatureC, 10, 30, 128, 255);
  } else {
      motorSpeed = 255;
  }
  if (lightPercent < 30) {
      motorSpeed = motorSpeed / 2;
  }
  motorSpeed = constrain(motorSpeed, 0, 255);

  if (moisturePercent < 40 && !lowWater) {
    analogWrite(MOTOR_PIN, motorSpeed);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(RED_LED, HIGH);
    tone(BUZZER, 1000, 500);
  } else if (lowWater) {
    analogWrite(MOTOR_PIN, 0);
    digitalWrite(YELLOW_LED, HIGH);
    digitalWrite(RED_LED, LOW);
    if (moisturePercent >= 40) {
      digitalWrite(GREEN_LED, HIGH);
    } else {
      digitalWrite(GREEN_LED, LOW);
      digitalWrite(RED_LED, HIGH);
    }
    tone(BUZZER, 2000, 300);
    delay(300);
  } else {
    analogWrite(MOTOR_PIN, 0);
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(RED_LED, LOW);
    noTone(BUZZER);
  }

  if (distance > 200) { 
    analogWrite(MOTOR2_PIN, 255);
  } else if (distance < 30) { 
    analogWrite(MOTOR2_PIN, 0);
  }

  delay(2000);
}
