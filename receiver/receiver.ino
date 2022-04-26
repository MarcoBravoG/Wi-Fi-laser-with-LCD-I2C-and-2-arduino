#define LED_PIN 3
#define LDR_PIN A2
#define THRESHOLD 100
#define PERIOD 15
#include <LiquidCrystal_I2C.h> //DESCARGAR LIBRERÍA:https://github.com/ELECTROALL/Codigos-arduino/blob/master/LiquidCrystal_I2C.zip
LiquidCrystal_I2C lcd(0x27,16,2); // si no te sale con esta direccion  puedes usar (0x3f,16,2) || (0x27,16,2)  ||(0x20,16,2) 

bool previous_state;
bool current_state;

void setup() 
{
    Serial.begin(9600);
    pinMode(LED_PIN, OUTPUT);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  //lcd.setCursor(0,0);
  //lcd.print("==> VIDEOS <=="); 
  //lcd.setCursor (0,1);
  //lcd.print("==> ELECTROMARK <");
}

void loop() 
{
  current_state = get_ldr();
  if(!current_state && previous_state)
  {
    print_byte(get_byte());
  }
  previous_state = current_state;
}

bool get_ldr()
{
  int voltage = analogRead(LDR_PIN);
  return voltage > THRESHOLD ? true : false;
}

char get_byte()
{
  char ret = 0;
  delay(PERIOD*1.5);
  for(int i = 0; i < 8; i++)
  {
   ret = ret | get_ldr() << i; 
   delay(PERIOD);
  }
  return ret;
}
void print_byte(char my_byte)
{
  char buff[2];
  sprintf(buff, "%c", my_byte);
  Serial.print(buff);
  lcd.print(buff);
 // delay(100);
  
}
