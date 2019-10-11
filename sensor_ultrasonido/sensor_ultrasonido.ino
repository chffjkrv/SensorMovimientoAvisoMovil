#include <SoftwareSerial.h>
SoftwareSerial DebugSerial(0, 1); // RX, TX
#include <BlynkSimpleStream.h>
#define BLYNK_PRINT DebugSerial
#define Pecho 6
#define Ptrig  7
#define Micro  8
int inputPin = 2;  // Establecemos el Pin del PIR
long duracion, distancia; 
int pirState = LOW;             
int val = 0;  
int pinValue = 0;
 
void setup() {                
  Serial.begin(9600);       // inicializa el puerto seria a 9600 baudios
  pinMode(Pecho,INPUT);     // define el pin 6 como entrada (echo)
  pinMode(Ptrig,OUTPUT);    // define el pin 7 como salida  (triger)
  pinMode(13,1);            // Define el pin 13 como salida
  pinMode(8,1);
  pinMode (buzzer,OUTPUT);
  }
  
void loop() {
  
digitalWrite(Ptrig, LOW);
delayMicroseconds(2);
digitalWrite(Ptrig, HIGH);   // genera el pulso de triger por 10ms
delayMicroseconds(10);
digitalWrite(Ptrig, LOW);
  
duracion = pulseIn(Pecho, HIGH);
distancia = (duracion/2) / 29;            // calcula la distancia en centimetros
  
  if (distancia >= 300 || distancia <= 0){  // si la distancia es mayor a 500cm o menor a 0cm 
    Serial.println("---");                  // no mide nada
  }
  else {
    Serial.print(distancia);           // envia el valor de la distancia por el puerto serial
    Serial.println("cm");              // le coloca a la distancia los centimetros "cm"
    digitalWrite(13,0);               // en bajo el pin 13
    digitalWrite(8,0);                 // el pin 8 en bajo
  }
  
   if (distancia <=  90& distancia >= 1){
    digitalWrite(12,1);     // en alto el pin 12 si la distancia es menor a 10cm
    digitalWrite(8,1);
    Serial.println("Alarma.......");         // envia la palabra Alarma por el puerto serial
    val = digitalRead(inputPin);
    digitalWrite(12, HIGH);
      if (val == HIGH) {
        Blynk.notify("Detecto movimiento, eres tú?");
      }
        else{
          digitalWrite(12, LOW);
        }
    Blynk.run();
    }
delay(400);  
}// espera 400ms para que se logre ver la distancia en la consola

