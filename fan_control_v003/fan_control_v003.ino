#include <math.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);
// arduino pins and I2C lcd pins
// GND (GND); 5V (Vcc); A4 (SDA); A5(SCL);

// fan wires
// Black = GND (0V)
// Yellow = +12V
// Green = Sense/Tach
// Blue = Control/PWM

int sense_pin = 0; // A0
int pwm_pin = 3;
int pwm_val = 0;
int prev_pwm_val = 0;

int count = 0;
int rpm; // revolutions per minute
unsigned long start_time;

void counter();
void print_pwm();
void print_rpm();

void setup()
{
  lcd.begin();
  lcd.backlight();
  pinMode(A0, INPUT);
  pinMode(pwm_pin, OUTPUT); // PWM pin
  //Serial.begin(9600);
  pinMode(2, INPUT_PULLUP); // pullup resistor for digita pin 2
  attachInterrupt(digitalPinToInterrupt(2), counter, RISING); // digital pin 2 to count pulses
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Fan PWM is "); // 11 symbols
  lcd.setCursor(0, 1);
  lcd.print("Fan RPM is ");
}


void loop()
{
  start_time = millis();
  pwm_val = int(analogRead(sense_pin)/1023.0*255.0) + 1; // 255=100% max PWM
  if(pwm_val < 100)
  {
    pwm_val = 0; // fan is not working on low PWM
  }
  else
  {
    if(pwm_val > 255)
    {
      pwm_val = 255;
    }
    
    if(prev_pwm_val == 0)
    {
      analogWrite(pwm_pin, 255); // to start rotating
    }
  }
  prev_pwm_val = pwm_val;
  count = 0;
  //delay(1000);
  //delay(500);
  while(millis() - start_time < 500)
  {
    print_pwm();
    print_rpm();
  }
  analogWrite(pwm_pin, pwm_val);

  // revolutions per minute
  //rpm = count*60/2; // delay is 1000ms and two pulses is one revolution
  rpm = count*60*2/2; // delay is 500ms and two pulses is one revolution
  
  //print_pwm();
  //print_rpm();
  
  //Serial.print("PWM value is ");
  //Serial.print(pwm_val);
  //Serial.print(", it is ");
  //Serial.print(rpm);
  //Serial.println(" revolutions per minute.");
}


void counter()
{
  count++;
}


void print_pwm()
{
  lcd.setCursor(13,0);
  if(pwm_val / 100 > 0)
  {
  }
  else if(pwm_val / 10 > 0)
  {
    lcd.print(" ");
  }
  else
  {
    lcd.print("  ");
  }
  lcd.print(pwm_val);
}


void print_rpm()
{
  lcd.setCursor(12,1);
  if(rpm / 1000 > 0)
  {
    
  }
  else if(rpm / 100 > 0)
  {
    lcd.print(" ");
  }
  else if(rpm / 10 > 0)
  {
    lcd.print("  ");
  }
  else
  {
    lcd.print("   ");
  }
  lcd.print(rpm);
}
