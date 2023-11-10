
// --- Mapeamento de Hardware  --- //
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

#define but 2         // botão conectado no pino 2 do Arduino

boolean t_but = false ; //variáveis flag inicia com false

const int ledPin1 = 12; // Pino do primeiro LED (altere conforme necess�rio)
const int ledPin2 = 13; // Pino do segundo LED (altere conforme necess�rio)

// Inicia a serial por software nos pinos 10 e 11
SoftwareSerial mySoftwareSerial(3, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
char buf;
bool ledsLigados = false; // Vari�vel para rastrear o estado dos LEDs
bool mp3Ligado = false; // Vari�vel para rastrear o estado do MP3
bool motorLigado = false; // Vari�vel para rastrear o estado do motor

class DCMotor {
  int spd = 255, pin1, pin2;
  
  public:
  void Attach(int in1, int in2) {
    pin1 = in1;
    pin2 = in2;
    pinMode(pin1, OUTPUT);
    pinMode(pin2, OUTPUT);
  }
  
  void Speed(int in1) {
    spd = in1;
  }
  
  void Forward() {
    analogWrite(pin1, spd);
    digitalWrite(pin2, LOW);
  }
  
  void Backward() {
    digitalWrite(pin1, LOW);
    analogWrite(pin2, spd);
  }
  
  void Stop() {
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
  }
};

DCMotor Motor1, Motor2;


void setup() {
  pinMode(but, INPUT);  //botão como entrada de sinal do botão
  
  // Comunica��o serial com o m�dulo
  mySoftwareSerial.begin(9600);
  
  // Inicializa a serial do Arduino
  Serial.begin(115200);
  
  // Verifica se o m�dulo est� respondendo e se o cart�o SD foi encontrado
  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini"));
  Serial.println(F("Inicializando m�dulo DFPlayer... (3~5 segundos)"));
  
  if(!myDFPlayer.begin(mySoftwareSerial)) {
    Serial.println(F("N�o inicializado:"));
    Serial.println(F("1. Cheque as conex�es do DFPlayer Mini"));
    Serial.println(F("2. Insira um cart�o SD"));
    while (true);
  }
  
  Serial.println();
  Serial.println(F("M�dulo DFPlayer Mini inicializado!"));
  
  // Defini��es iniciais
  myDFPlayer.setTimeOut(500); // Timeout serial 500ms
  myDFPlayer.volume(5); // Volume 5
  myDFPlayer.EQ(0); // Equaliza��o normal
  
  Motor1.Attach(5, 6);
  Motor2.Attach(9, 10);
  
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  
  // Define o pino do bot�o como entrada com resistor de pull-up interno
  pinMode(but, INPUT);  //botão como entrada de sinal

}

void loop() {
 if(!digitalRead(but)) t_but = true;           // Botão Up pressionado? Seta flag

  if(digitalRead(but) && t_but)                 // Botão
    {     // Sim...
    //unsigned long tempoPressionado = millis(); // Marca o tempo de pressionamento
    
    // Atraso de 2 segundos antes de ligar os LEDs
    // while (millis() - tempoPressionado < 1000) {
      // Nada acontece, apenas espera
    //}

    digitalWrite(ledPin1, HIGH); // Liga o primeiro LED
    digitalWrite(ledPin2, HIGH); // Liga o segundo LED
    ledsLigados = true; // LEDs agora est�o ligados

    // Atraso de 3 segundos antes de ligar o MP3
    //while (millis() - tempoPressionado < 3000) {
      // Nada acontece, apenas espera
    //}

    // Reproduz a m�sica n�mero 1
    myDFPlayer.play(1);
    myDFPlayer.volume(20); // Define o volume para 30
    
    Serial.println("Iniciando m�sica n�mero 1...");
    mp3Ligado = true; // MP3 agora est� ligado
    
    // Atraso de mais 3 segundos antes de ligar o motor
    while (millis() - tempoPressionado < 12000) {
      // Nada acontece, apenas espera
    }
  
    // Definindo a velocidade inicial (baixa)
    int initialSpeed = 70; // Pode ser ajustado conforme necess�rio
    
    // Girando ambos os motores com velocidade baixa por 1 minuto e 30 segundos
    unsigned long startTime = millis();
    while (millis() - startTime <= 80000) { // 1 minuto e 30 segundos em milissegundos
    Motor1.Speed(initialSpeed);
    Motor2.Speed(initialSpeed);
    Motor1.Forward();
    Motor2.Forward();
  }

  // Aumentando a velocidade
  int increasedSpeed = 135; // Velocidade aumentada
  Motor1.Speed(increasedSpeed);
  Motor2.Speed(increasedSpeed);
  
  // Girando os motores com a nova velocidade por 1 minuto
  unsigned long newStartTime = millis();

  while (millis() - newStartTime <= 71500) { // 1 minuto em milissegundos
    Motor1.Forward(); 
    Motor2.Forward();
  }

  // Parando os motores
  Motor1.Stop();
  Motor2.Stop();

  // Aguardando um curto per�odo de tempo (30 segundos)
  delay(5000); // 3 segundos em milissegundos
  
  // Definindo uma nova velocidade (40)
  int finalSpeed = 60; // Velocidade final
  
  // Girando ambos os motores com a nova velocidade por 30 segundos
  unsigned long finalStartTime = millis();
  
  while (millis() - finalStartTime <= 53000) { // 30 segundos em milissegundos
    Motor1.Speed(finalSpeed);
    Motor2.Speed(finalSpeed);
    Motor1.Forward();
    Motor2.Forward();
  }

  // Parando os motores novamente
  Motor1.Stop();
  Motor2.Stop();

  // Desligando os LEDs
    //Serial.println("desligar leds");

  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, LOW);
  //Serial.println(ledsLigados);

  // Reiniciando o estado    
  ledsLigados = false;

  // Aguardando um tempo antes de reiniciar o loop
  //while (digitalRead(2) == HIGH) {
    // Aguarda at� que o bot�o seja pressionado novamente
    delay(1000); // Adiciona um pequeno atraso de 100 milissegundos
  //}
  //Serial.println(estadoBotaoAtual);
  //Serial.println(ledsLigados);
      t_but = false;                                // Limpa o flag

    } // End but
}
