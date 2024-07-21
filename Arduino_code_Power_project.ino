#include <math.h>

#define WINDOW_SIZE 128
int numSamples = WINDOW_SIZE;
float piValue = 3.14159265358979323846;

long double phaseA_values[WINDOW_SIZE];
long double phaseB_values[WINDOW_SIZE];
long double phaseC_values[WINDOW_SIZE];

float X_real_A, X_imaginary_A, magnitude_A, angle_A;
float X_real_B, X_imaginary_B, magnitude_B, angle_B;
float X_real_C, X_imaginary_C, magnitude_C, angle_C;

const int ANALOG_PIN_A = A0;  // Analog pin for Phase A
const int ANALOG_PIN_B = A1;  // Analog pin for Phase B
const int ANALOG_PIN_C = A2;  // Analog pin for Phase C

void setup() {
  Serial.begin(115200);
  // Set analog reference to DEFAULT (5V)
  analogReference(DEFAULT);
}

void loop() {
  calculatePhasors();
  plotPhasors();

  delay(1000); // Delay for 1 second before the next iteration
}

void calculatePhasors() {
  for (int i = 0; i < numSamples; i++) {
    phaseA_values[i] = analogRead(ANALOG_PIN_A); // Phase A
    phaseB_values[i] = analogRead(ANALOG_PIN_B); // Phase B
    phaseC_values[i] = analogRead(ANALOG_PIN_C); // Phase C
  }

  X_real_A = X_imaginary_A = X_real_B = X_imaginary_B = X_real_C = X_imaginary_C = 0;

  for (int n = 0; n < numSamples; n++) {
    X_real_A += phaseA_values[n] * cos((2 * piValue * n) / numSamples);
    X_imaginary_A += phaseA_values[n] * sin((2 * piValue * n) / numSamples);

    X_real_B += phaseB_values[n] * cos((2 * piValue * n) / numSamples);
    X_imaginary_B += phaseB_values[n] * sin((2 * piValue * n) / numSamples);

    X_real_C += phaseC_values[n] * cos((2 * piValue * n) / numSamples);
    X_imaginary_C += phaseC_values[n] * sin((2 * piValue * n) / numSamples);
  }

  magnitude_A = sqrt(X_real_A * X_real_A + X_imaginary_A * X_imaginary_A);
  magnitude_B = sqrt(X_real_B * X_real_B + X_imaginary_B * X_imaginary_B);
  magnitude_C = sqrt(X_real_C * X_real_C + X_imaginary_C * X_imaginary_C);

  angle_A = atan2(X_imaginary_A, X_real_A) * (180.0 / piValue);
  angle_B = atan2(X_imaginary_B, X_real_B) * (180.0 / piValue);
  angle_C = atan2(X_imaginary_C, X_real_C) * (180.0 / piValue);
}

void plotPhasors() {
  for (int i = 0; i < numSamples; i++) {
    double sample_A = magnitude_A * sin((2 * piValue * i) / numSamples + angle_A * (piValue / 180.0));
    double sample_B = magnitude_B * sin((2 * piValue * i) / numSamples + angle_B * (piValue / 180.0));
    double sample_C = magnitude_C * sin((2 * piValue * i) / numSamples + angle_C * (piValue / 180.0));

    Serial.print(angle_A);
    Serial.print(",");
    Serial.print(angle_B);
    Serial.print(",");
    Serial.println(angle_C);
  }
}
