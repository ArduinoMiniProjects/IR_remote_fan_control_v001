/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 modified 7 Nov 2016
 by Arturo Guadalupi

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystalHelloWorld

*/

// include the library code:
#include <LiquidCrystal.h>
#include <IRremote.h>

IRrecv irrecv(6);
decode_results results;


// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int PWM_val;
int level_val;
int previous_PWM_val;
const int pwm_pin = 9;

void setup() 
{
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  //lcd.setCursor(0, 0);
  //lcd.print("Value of button");
  lcd.setCursor(0,0);
  lcd.print("  Fan level   0 ");
  lcd.setCursor(0,1);
  lcd.print(" PWM value    0 ");

  PWM_val = 0;
  level_val = 0;
  previous_PWM_val = 0;
  pinMode(pwm_pin, OUTPUT); // PWM pin
  
  irrecv.enableIRIn(); // Uzsakt uztversanu
}


void loop() 
{
  if (irrecv.decode(&results)) // if we have received an IR signal
  {   
      switch(results.value)
      {
        case 0xE13DDA28:  // button 1
        level_val = 1;
        break;

        case 0xAD586662: // button 2
        level_val = 2;
        break;

        case 0x273009C4: // button 3 
        level_val = 3;
        break;

        case 0xF5999288: // button 4 
        level_val = 4;
        break;

        case 0x731A3E02: // button 5
        level_val = 5;
        break;

        case 0x2C452C6C: // button 6  
        level_val = 6;
        break;

        case 0x4592E14C:  // button 7
        level_val = 7;
        break;

        case 0x6825E53E: // button 8
        level_val = 8;
        break;

        case 0x8B8510E8: // button 9 
        level_val = 9;
        break;

        case 0xB9F56762: // button 0 
        level_val = 0;
        break;

        case 0x5F12E8C4: // button 'up'
        if(level_val < 9)
        {
          level_val = level_val + 1;
        }
        break;

        case 0x189D7928: // button 'down'  
        if(level_val > 0)
        {
          level_val = level_val - 1;
        }
        break;
        
        default: 
        break;
      }

      
      
      switch(level_val)
      {
        case 1:  
        PWM_val = 55;
        break;

        case 2:
        PWM_val = 75;
        break;

        case 3: 
        PWM_val = 100;
        break;

        case 4: 
        PWM_val = 125;
        break;

        case 5:
        PWM_val = 150;
        break;

        case 6:  
        PWM_val = 175;
        break;

        case 7:
        PWM_val = 200;
        break;

        case 8: 
        PWM_val = 225;
        break;

        case 9: 
        PWM_val = 255;
        break;

        case 0:
        PWM_val = 0;
        break;
        
        default: 
        break;
      }


      lcd.setCursor(14,0);
      lcd.print(level_val);
      lcd.setCursor(12,1);
      if(PWM_val / 100 > 0)
      {
      }
      else if(PWM_val / 10 > 0)
      {
        lcd.print(" ");
      }
      else
      {
        lcd.print("  ");
      }
      lcd.print(PWM_val);

      if(previous_PWM_val == 0)
      {
        analogWrite(pwm_pin, 255);
        delay(1500);
        previous_PWM_val = PWM_val;
      }
      analogWrite(pwm_pin, PWM_val);
      
      irrecv.resume(); // next value
  }
  delay(200);
}
