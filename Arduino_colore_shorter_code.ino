
#include <Servo.h>
#include <Stepper.h>

//Pin de Sensor de Color  -  Pin Arduino
#define S0 4 
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8

//Pin de servo a pin 9 arduino
#define agujaIn 9

//Pun de Motor a Pasos  -  Pin Arduino
#define M1 10
#define M2 11
#define M3 12
#define M4 13


Servo aguja;
Stepper motor(2048, M1, M3, M2, M4);
int colorNow=0;
int colorNext=0;

void setup() {
  Serial.begin(9600);
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  pinMode(agujaIn, OUTPUT);
  aguja.attach(agujaIn);
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  pinMode(M3, OUTPUT);
  pinMode(M4, OUTPUT);
  motor.setSpeed(10);
  pinMode(LED_BUILTIN, OUTPUT);
  
  digitalWrite(S0,LOW);
  digitalWrite(S1,HIGH);
}

void loop() {
  colorNext = readColor();
  Serial.print(" Now: ");
  Serial.print(colorNow);
  
  switch (colorNow) {
    case 0:
    Serial.print(" Next: ");
    Serial.println(colorNext);
    digitalWrite(LED_BUILTIN, LOW);
    aguja.write(40);
    break;
    
    case 1:
    Serial.print(" Next: ");
    Serial.println(colorNext);
    digitalWrite(LED_BUILTIN, HIGH);
    aguja.write(135);
    break;
  }
  delay(800);
  colorNow=colorNext;
  motor.step(map(90, 0, 360, 0, 2048));
  
}

int readColor() {
  
  //Lectura de fotodiodos con filtro rojo
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  int R = pulseIn(sensorOut, LOW);
  Serial.print("R=");
  Serial.print(R);
  Serial.print("  ");
  
  //Lectura de fotodiodos con filtro verde
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  int G = pulseIn(sensorOut, LOW);
  Serial.print("G=");
  Serial.print(G);
  Serial.print("  ");
  
  //Lectura de fotodiodos con filtro azul
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  int B = pulseIn(sensorOut, LOW);
  Serial.print("B=");
  Serial.print(B);
  Serial.print("  ");
  
  int color = 0;
  
  if(G>30 & G<46 & B<60){ //Calibrar rangos con cafe real
    color = 1; // Yellow
  }
  
  return color;  
}
