# Projeto PWM Motor com Arduino

## Índice
1. [Introdução ao PWM](#introdução-ao-pwm)
2. [Componentes necessários](#componentes-necessários)
3. [Esquemático](#esquemático)
4. [Código-fonte](#código-fonte)
5. [Instruções de montagem](#instruções-de-montagem)
6. [Funcionamento do projeto](#funcionamento-do-projeto)

## Introdução ao PWM
Neste projeto, é utilizado o conceito de Modulação por Largura de Pulso (PWM) para controlar a velocidade de um motor utilizando um Arduino Nano e um driver de motor L293D.

## Componentes necessários
- Motor
- Arduino Nano
- Driver de motor L293D
- Botão
- Resistor

## Esquemático
![Esquemático do PWM Controller](schematics/pwm_controller_schematic.pdf)


## Código-fonte
```cpp
#include <Arduino.h>

const int motorPin = 9;  // Pino onde o motor está conectado
const int buttonPin = 2; // Pino onde o botão está conectado
int motorSpeed = 0;      // Variável para armazenar a velocidade do motor (0% inicialmente)
int buttonState;         // Variável para armazenar o estado do botão
int lastButtonState = HIGH; // Último estado do botão, inicializado como HIGH para INPUT_PULLUP
unsigned long lastDebounceTime = 0; // Tempo do último debounce
unsigned long debounceDelay = 50;   // Delay de debounce

void setup() {
  pinMode(motorPin, OUTPUT);      // Configura o pino do motor como saída
  pinMode(buttonPin, INPUT_PULLUP); // Configura o pino do botão como entrada com pull-up interno
  Serial.begin(9600);              // Inicializa a comunicação serial
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
      if (buttonState == LOW) { // Botão pressionado (LOW devido ao INPUT_PULLUP)
        // Aumenta a velocidade do motor em 25%
        motorSpeed += 64;
        if (motorSpeed > 255) {
          motorSpeed = 0; // Reseta a velocidade do motor para 0% quando ultrapassa 100%
        }
        analogWrite(motorPin, motorSpeed); // Atualiza a velocidade do motor
        Serial.print("Motor Speed: ");      // Imprime a velocidade atual no console serial
        Serial.println(motorSpeed);
      }
    }
  }

  lastButtonState = reading; // Atualiza o último estado do botão
}
```
## Instruções de montagem
Siga estas etapas para montar o circuito do projeto:

1. Conecte o motor ao driver de motor L293D. Certifique-se de conectar os fios corretamente aos terminais do driver.
2. Conecte o driver de motor L293D ao Arduino Nano. Utilize os pinos adequados para as conexões de entrada e saída.
3. Conecte um botão ao Arduino Nano. Certifique-se de utilizar um resistor de pull-up interno ou externo, conforme necessário.
4. Verifique se todas as conexões estão firmes e corretas.
5. Faça o upload do código-fonte para o Arduino Nano utilizando a IDE do Arduino.
6. Após o upload bem-sucedido, alimente o circuito com a energia necessária.
7. Pressione o botão para controlar a velocidade do motor conforme descrito no funcionamento do projeto.

Certifique-se de seguir as instruções com cuidado e tome as precauções de segurança necessárias ao lidar com eletricidade e componentes eletrônicos.

## Funcionamento do projeto
O projeto utiliza um botão para controlar a velocidade de um motor. Quando o botão é pressionado, a velocidade do motor aumenta em 25% até atingir 100%, momento em que a velocidade é resetada para 0%.

O código utiliza o conceito de debouncing para garantir que apenas uma única pressão de botão seja registrada, evitando leituras falsas devido a oscilações elétricas. Isso é importante para garantir um controle preciso da velocidade do motor.

Ao pressionar o botão, o Arduino lê o estado atual do botão e compara com o estado anterior após um período de debounce. Se detectar uma mudança no estado do botão e o tempo de debounce tiver passado, o Arduino aumenta a velocidade do motor em 25%. Quando a velocidade atinge 100%, ela é resetada para 0% e o ciclo se repete.

Este projeto demonstra um exemplo simples de controle de motor utilizando PWM e um botão com Arduino.
