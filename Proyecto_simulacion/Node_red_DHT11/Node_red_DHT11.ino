#include <avr/io.h>


#define VENTILADOR PB4 //PIN12
#define FOCO1 PB1       //PIN 9
#define FOCO2 PB2       //PIN 10
#define FOCO3 PB3       //PIN 11

int F1 = 0;
int F2 = 0;
int F3 = 0;
int Vent = 0;

void setup() 
{
  DDRB |=  (1<<FOCO1) | (1<<FOCO2)| (1<<FOCO3) | (1<<VENTILADOR) ; // SE ENCUENTRAN CONFIGURADOS COMO SALIDAS
  Serial.begin(9600);

}

void loop() 
{
  delay(500);
  
  float TemC  = (analogRead(A0)/1023.0)*5*100.0;    //lee temperatura en celsius
  float TemC1 = (analogRead(A1)/1023.0)*5*100.0;    //lee temperatura en celsius
   delay(1000);                       // wait for a second
  
  //verificacion de conexion 
  if(isnan(TemC) || isnan(TemC1) /* || isnan(Humd)*/ ) //si no lee dato numerico
  {
    Serial.println("Revisar Conexion");  
  }
  else
  {

// FASE 1    
   if (TemC<=27)
    { 
      F1 = 1 ;
      F2 = 1 ;
      PORTB |=(1<<FOCO1);               // ENCENDEMOS LA LAMPARA
      PORTB |=(1<<FOCO2);               // ENCENDEMOS LA LAMPARA
      delay(1000);                     // wait for a second
      
      } 
    if (TemC>=34)
    {
      F1 = 0 ;
      F2 = 0 ;
      PORTB &=~(1<<FOCO1); ;         // APAGAMOS LA LAMPARA
      PORTB &=~(1<<FOCO2); ;         // APAGAMOS LA LAMPARA
      delay(1000);                 // wait for a second
      
      }  
// FASE 2
    if (TemC1<=24)
    { 
      F3 = 1 ;
      Vent = 0;
      PORTB |=(1<<FOCO3);               // ENCENDEMOS LA LAMPARA
      delay(1000);                     // wait for a second
      PORTB &=~(1<<VENTILADOR);         // APAGAMOS EL MOTOR
      } 
    if (TemC1>=30)
    {
      F3 = 0 ;
      Vent = 1;
      PORTB &=~(1<<FOCO3); ;         // APAGAMOS LA LAMPARA
      delay(1000);                 // wait for a second
      PORTB |=(1<<VENTILADOR); ;   // ENCENDEMOS EL MOTOR
      } 
    //Temperatura : __C ;foco
    
    //String Mensaje =fase1 - fase 2;fase1= tempC,foco1,foco2; fase2=tempC,foco3,Ventilador
    String Mensaje = String(TemC,2)+","+String(F1)+","+String(F2)+"-"+String(TemC1,2)+","+String(F3)+","+String(Vent);
    Serial.println(Mensaje);
  }

}
