// Code voor het uitlezen van IR sensoren en aansturen van de bijbehorende leds
// Plus opzet voor aansturing servo's

// TEST SERVO AANTURING MET LIBRARY
#include <Servo.h>
Servo servoL;
Servo servoR;
void Servosturing(int, int);


// Pins die door de functie gebruikt worden
const int IRpin_l = A5; 
const int IRpin_m = A6;
const int IRpin_r = A7;
const int LEDpin_l = 3;
const int LEDpin_m = 4;
const int LEDpin_r = 5;
// Grenswaarde IR sensoren (nog niet geoptimaliseerd)
const int CompareValue_IR = 512;

// Globale variabele om laatste uitlezeing te bewaren
char ReturnValue_IR = 0;

// Prototypes sensoren
char IRsensorRead(void);
void IRcase(char);
void IRcaseLED(char);


void setup()  // Leds als OUTPUT instellen
{
  servoL.attach(10);
  servoR.attach(11);
  pinMode(LEDpin_l, OUTPUT);
  pinMode(LEDpin_m, OUTPUT);
  pinMode(LEDpin_r, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  char IRsensorOutput = IRsensorRead();
  IRcase(IRsensorOutput);
  IRcaseLED(IRsensorOutput);
}

char IRsensorRead(void)
{
  int IRvalue_l = 0;
  int IRvalue_m = 0;
  int IRvalue_r = 0;

// Inverteert de waardes van de sensoren zodat detectie = hoge waarde
  IRvalue_l = 1024 - analogRead(IRpin_l);
  IRvalue_m = 1024 - analogRead(IRpin_m);
  IRvalue_r = 1024 - analogRead(IRpin_r);
//  DEBUG
//  Serial.print(IRvalue_l);
//  Serial.print("\t");
//  Serial.print(IRvalue_m);
//  Serial.print("\t");
//  Serial.print(IRvalue_r);
//  Serial.print("\n");
 

  if(IRvalue_l > CompareValue_IR || IRvalue_m > CompareValue_IR || IRvalue_r > CompareValue_IR)
  {
    if(IRvalue_l > CompareValue_IR) ReturnValue_IR |= 0x01; else ReturnValue_IR &= ~(0x01);
    if(IRvalue_m > CompareValue_IR) ReturnValue_IR |= 0x02; else ReturnValue_IR &= ~(0x02);
    if(IRvalue_r > CompareValue_IR) ReturnValue_IR |= 0x04; else ReturnValue_IR &= ~(0x04);
  }
  return ReturnValue_IR;
}

void IRcase(char w)
{
  switch(w)
  {
    case 0x01:
    {
      Servosturing(1400,1400);
      //stuur scherp links
    }
    break;
  
    case 0x02:
    {
      Servosturing(1400,1600);
      // rij rechtdoor
    }
    break;
    
    case 0x03:
    {
      Servosturing(1400,1500);
      // stuur langzaam links
    }
    break;
  
    case 0x04:
    {
      Servosturing(1600,1600);
      // stuur scherp rechts
    }
    break;
  
    case 0x06:
    {
      Servosturing(1500,1600);
      // stuur langzaam rechts
    }
    break;
    case 0x07:
    {
      Servosturing(1400,1600);
      // rechtdoor (alle sensoren HIGH)
    }
  
    default:
    {
      // rondje draaien (leader kwijt)
    }
  }
}

void IRcaseLED(char LEDs)
{
  digitalWrite(LEDpin_l, LOW);
  digitalWrite(LEDpin_m, LOW);
  digitalWrite(LEDpin_r, LOW);
  switch(LEDs)
  {
    case 0x01:
    {
      digitalWrite(LEDpin_l, HIGH);
//      Serial.println("links");
    }
    break;
  
    case 0x02:
    {
      digitalWrite(LEDpin_m, HIGH);
//      Serial.println("midden");
    }
    break;

    case 0x03:
    {
      digitalWrite(LEDpin_l, HIGH);
      digitalWrite(LEDpin_m, HIGH);
//      Serial.println("linksmidden");
    }
    break;
  
    case 0x04:
    {
      digitalWrite(LEDpin_r, HIGH);\
//      Serial.println("rechts");
    }
    break;

    case 0x06:
    {
      digitalWrite(LEDpin_r, HIGH);
      digitalWrite(LEDpin_m, HIGH);
//      Serial.println("rechtsmidden");
    }
    break;

    case 0x07:
    {
      digitalWrite(LEDpin_l, HIGH);
      digitalWrite(LEDpin_m, HIGH);
      digitalWrite(LEDpin_r, HIGH);
//      Serial.println("midden");
    }
    break;
  }
}

void Servosturing(int Links, int Rechts)
{       
      servoL.writeMicroseconds(Links);
      servoR.writeMicroseconds(Rechts);
}
