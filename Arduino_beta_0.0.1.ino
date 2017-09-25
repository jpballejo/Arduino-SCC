#include <string.h>
#include <stdio.h>
#include <SimpleDHT.h>
const long A = 1000;     //Resistencia en oscuridad en KΩ
const int B = 15;        //Resistencia a la luz (10 Lux) en KΩ
const int Rc = 10;       //Resistencia calibracion en KΩ
const int LDRPin = A0;   //Pin del LDR
int pinDHT11 = 2;
SimpleDHT11 dht11;
byte hum=0,temp=0;
void setup() {
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  
Serial.begin (9600);  // put your setup code here, to run once:
}

void loop() {
  if(Serial.available()>0)seleccion(Serial.read());
  controlHumedad();
  }
//////////////////////////////////FUCIONES//////////////////////////////////////

//lee los comandos que le vienen al serial
void seleccion(char pal){
  if (strcmp("Luz",pal)==0)iluminacion();
  if (strcmp("Humedad plantas",pal)==0)leerhumedad("A1");
  if (strcmp("Humedad hambiente",pal)==0)humedadh();
  if (strcmp("Temperatura hambiente",pal)==0)temperatura();
  }
///////////////////////////////LUZ///////////////////////////////
  void iluminacion(){
    int ilum = 0;
    int V = analogRead(LDRPin); //voltaje del pin
  //conversion:
  //ilum = ((long)(1024-V)*A*10)/((long)B*Rc*V);  //usar si LDR entre GND y A0 
    ilum=((long)V*A*10)/((long)B*Rc*(1024-V));    //usar si LDR entre A0 y Vcc (como en el esquema anterior)
    Serial.write(ilum);
  }
 /////////////////////////////////Humedad Hambiente/////////////////
  void humedadh(){
    dht11.read(pinDHT11,&hum,&temp,NULL);
    Serial.write(hum);
    }
 ///////////////////////////////Temperatura Hambiente///////////////
  void temperatura (){
      dht11.read(pinDHT11,&hum,&temp,NULL);
      Serial.write(temp);}
 ///////////////////////////////Humedad planta (pin)//////////////////
 int leerhumedad(char pin){
      int hum =0;
      hum=map(analogRead(pin),0,1023,100,0);
   return hum;}
 ////////////////////////Control///////////////////////////
  void controlHumedad(){
    int hume=leerhumedad("A1");
    if (hume <= 20) {
        digitalWrite(4,HIGH);
        digitalWrite(5,HIGH);
        while (hume<50){
          hume=leerhumedad("A1");
          if(hume<=49){digitalWrite(4,LOW);
          digitalWrite(6,LOW);}
          }
        }
      }

