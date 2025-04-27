#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// Erstelle ein PCA9685-Objekt
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// Servoparameter
#define SERVOMIN 150 // Minimum Pulswert (0 Grad)
#define SERVOMAX 600 // Maximum Pulswert (180 Grad)

// Servokanäle auf dem PCA9685
const int servoChannels[] = {0, 1, 2, 3, 4, 5}; // Kanäle für die Servos
const int numServos = sizeof(servoChannels) / sizeof(servoChannels[0]);

// Initialisierung der Servopositionen (alle auf 90 Grad)
int servoAngles[numServos] = {90, 90, 90, 90, 90, 90};

// Funktion zum Umrechnen von Grad in Pulsweite
uint16_t angleToPulse(int angle) {
  return map(angle, 0, 180, SERVOMIN, SERVOMAX);
}

// Funktion zum Setzen der Servo-Winkel
void setServoPositions(const int angles[], int length) {
  for (int i = 0; i < length && i < numServos; i++) {
    servoAngles[i] = constrain(angles[i], 0, 180); // Winkel auf gültigen Bereich beschränken
    pwm.setPWM(servoChannels[i], 0, angleToPulse(servoAngles[i]));
  }
}

void setup() {
  Serial.begin(9600);
  Serial.println("Starte PCA9685...");

  // Initialisiere PCA9685
  pwm.begin();
  pwm.setPWMFreq(50); // PWM-Frequenz auf 50 Hz für Servos

  delay(10); // Kurze Pause, um sicherzustellen, dass alles bereit ist

  // Initialisiere alle Servos auf 90 Grad
  setServoPositions(servoAngles, numServos);
}

void loop() {
  // Beispiel: Ansteuern der Servos mit einer neuen Position
  int newPositions[] = {45, 135, 90, 60, 120, 30}; // Neue Zielpositionen
  setServoPositions(newPositions, numServos);
  delay(2000); // Warte 2 Sekunden

  // Zurück zu den ursprünglichen Positionen
  int resetPositions[] = {90, 90, 90, 90, 90, 90};
  setServoPositions(resetPositions, numServos);
  delay(2000); // Warte 2 Sekunden
}
