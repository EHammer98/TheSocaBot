// Code voor het uitlezen van IR sensoren en aansturen van de bijbehorende leds
// Plus opzet voor aansturing servo's

const int IRpin_l = A5;   // Pins die door de functie gebruikt worden
const int IRpin_m = A6;
const int IRpin_r = A7;
const int LEDpin_l = 3;
const int LEDpin_m = 4;
const int LEDpin_r = 5;

char IRsensorRead(void);

void setup()  // Leds als OUTPUT instellen
{
  pinMode(LEDpin_l, OUTPUT);
  pinMode(LEDpin_m, OUTPUT);
  pinMode(LEDpin_r, OUTPUT);
}

void loop()
{
  char IRsensorOutput = IRsensorRead();
  //IRcase(IRsensorOutput);
  IRcaseLED(IRsensorOutput);
}


char IRsensorRead(void)  // leest IR sensoren twee keer uit met een delay ertussen en vergelijkt met grenswaarde
{
   int IRvalue_l1 = 0;
   int IRvalue_m1 = 0;
   int IRvalue_r1 = 0;
   int IRvalue_l2 = 0;
   int IRvalue_m2 = 0;
   int IRvalue_r3 = 0;
   int CompareValue_IR = 300;
   char ReturnValue_IR;

   IRvalue_l1 = analogRead(IRpin_l);
   IRvalue_m1 = analogRead(IRpin_m);
   IRvalue_r1 = analogRead(IRpin_r);
   delay(5);
   IRvalue_l2 = analogRead(IRpin_l);
   IRvalue_m2 = analogRead(IRpin_m);
   IRvalue_r2 = analogRead(IRpin_r);

   if(IRvalue_l1 < CompareValue_IR || IRvalue_l2 < CompareValue_IR) ReturnValue_IR |= 0x01; else ReturnValue_IR &= ~(0x01);
   if(IRvalue_m1 < CompareValue_IR || IRvalue_m2 < CompareValue_IR) ReturnValue_IR |= 0x02; else ReturnValue_IR &= ~(0x02);
   if(IRvalue_r1 < CompareValue_IR || IRvalue_r2 < CompareValue_IR) ReturnValue_IR |= 0x04; else ReturnValue_IR &= ~(0x04);

   return ReturnValue_IR;
}

//void IRcase(char w)
//{
//  switch(w)
//  case 0x01:
//  {
//    //stuur scherp links
//  }
//  break;
//
//  case 0x02:
//  {
//    // rij rechtdoor
//  }
//  break;
//  
//  case 0x03:
//  {
//    // stuur langzaam links
//  }
//  break;
//
//  case 0x04:
//  {
//    // stuur scherp rechts
//  }
//  break;
//
//  case 0x06:
//  {
//    // stuur langzaam rechts
//  }
//  break;
//  case 0x07:
//  {
//    // rechtdoor (alle sensoren HIGH)
//  }
//
//  default:
//  {
//    // rondje draaien (leader kwijt)
//  }
//  
//}

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
      Serial.println("links");
    }
    break;
  
    case 0x02:
    {
      digitalWrite(LEDpin_m, HIGH);
      Serial.println("midden");
    }
    break;

    case 0x03:
    {
      digitalWrite(LEDpin_l, HIGH);
      digitalWrite(LEDpin_m, HIGH);
      Serial.println("linksmidden");
    }
    break;
  
    case 0x04:
    {
      digitalWrite(LEDpin_r, HIGH);\
      Serial.println("rechts");
    }
    break;

    case 0x06:
    {
      digitalWrite(LEDpin_r, HIGH);
      digitalWrite(LEDpin_m, HIGH);
      Serial.println("rechtsmidden");
    }
    break;

    case 0x07:
    {
      digitalWrite(LEDpin_l, HIGH);
      digitalWrite(LEDpin_m, HIGH);
      digitalWrite(LEDpin_r, HIGH);
      Serial.println("midden");
    }
    break;
  }
}
