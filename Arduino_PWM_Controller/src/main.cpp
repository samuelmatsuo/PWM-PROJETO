#include <Arduino.h>

const int motorPin = 9;  // Pino onde o motor está conectado
const int buttonPin = 2; // Pino onde o botão está conectado
int motorSpeed = 0;      // Variável para armazenar a velocidade do motor (0% inicialmente)
int buttonState;         // Variável para armazenar o estado do botão
int lastButtonState = LOW; // Último estado do botão
unsigned long lastDebounceTime = 0; // Tempo do último debounce
unsigned long debounceDelay = 50;   // Delay de debounce

void setup() {
  pinMode(motorPin, OUTPUT);     // Configura o pino do motor como saída
  pinMode(buttonPin, INPUT);     // Configura o pino do botão como entrada
  analogWrite(motorPin, motorSpeed); // Inicializa o motor com velocidade 0% (motorSpeed = 0)
}

void loop() {
  int reading = digitalRead(buttonPin); // Lê o estado atual do botão

  // Verifica se o botão foi pressionado (considerando o debounce)
  if (reading != lastButtonState) {
    lastDebounceTime = millis(); // Registra o tempo da última mudança de estado
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // Se o estado do botão mudou e o tempo de debounce passou
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == HIGH) {
        // Aumenta a velocidade do motor em 25%
        motorSpeed += 64;
        if (motorSpeed > 255) {
          motorSpeed = 0; // Reseta a velocidade do motor para 0% quando ultrapassa 100%
        }
        analogWrite(motorPin, motorSpeed); // Atualiza a velocidade do motor
      }
    }
  }

  lastButtonState = reading; // Atualiza o último estado do botão
}
