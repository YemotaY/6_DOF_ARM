#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// Erstellen des PCA9685-Objekts
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// Definition der Servo-Pins
const int servoCount = 6;
const int servoPins[servoCount] = {0, 1, 2, 3, 4, 5};

// Kalibrierung der Pulsbreiten (diese Werte können je nach Servo variieren)
const int servoMin = 150; // Pulswert für 0 Grad
const int servoMax = 600; // Pulswert für 180 Grad

// Funktion zum Konvertieren von Grad in Pulsweiten
int angleToPulse(int angle) {
  return map(angle, 0, 180, servoMin, servoMax);
}

void setup() {
  Serial.begin(9600);
  Serial.println("PCA9685 Servo Test");

  // Initialisierung des PCA9685
  pwm.begin();
  pwm.setPWMFreq(50); // Servos arbeiten normalerweise mit 50 Hz

  // Referenzierung: Setze alle Servos auf 90 Grad
  for (int i = 0; i < servoCount; i++) {
    pwm.setPWM(servoPins[i], 0, angleToPulse(90));
  }
  delay(1000); // Eine Sekunde warten, damit sich die Servos bewegen können
}

void loop() {
  // Beispiel: Servo-Positionen einstellen (kann später durch Steuerung ersetzt werden)
  int positions[servoCount] = {90, 90, 90, 90, 90, 90}; // Standardpositionen

  // Positionen auslesen (kann später aus einer Eingabequelle wie einem Controller kommen)
  Serial.println("Gebe Positionen in Grad ein (z. B. 90,90,90,90,90,90):");
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    sscanf(input.c_str(), "%d,%d,%d,%d,%d,%d",
           &positions[0], &positions[1], &positions[2],
           &positions[3], &positions[4], &positions[5]);
  }

  // Positionen auf die Servos anwenden
  for (int i = 0; i < servoCount; i++) {
    int pulse = angleToPulse(positions[i]);
    pwm.setPWM(servoPins[i], 0, pulse);
  }

  delay(1000); // Eine Sekunde warten, bevor der nächste Zyklus beginnt
}
