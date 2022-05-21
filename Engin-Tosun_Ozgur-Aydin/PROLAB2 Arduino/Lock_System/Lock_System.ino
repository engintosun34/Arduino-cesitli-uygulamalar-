
#include<Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F,20,4);

char tuslar[4][3]={ // keypadi char dizisi ile tanımlama
 {'1','2','3'},
 {'4','5','6'},
 {'7','8','9'},
 {'*','0','#'}};
 
byte rowPin[4]={6,7,8,9}; // keypade bağlama pinleri
byte colPin[3]={3,4,5};

String sifre = "2587";  // sifremiz.
int position = 0;

int wrong = 0; // Yanlış girdileri hesaplamak için değişken.


int redPin = 10;
int greenPin = 11;

 
Keypad keypad=Keypad(makeKeymap(tuslar),rowPin,colPin,4,3);
// KLAVYE HARİTASI.



int total = 0; // Yanlış denemelerin sayısını belirlemek için değişken.

void setup() // kurulumlar
{
  
 pinMode(redPin,OUTPUT);
 pinMode(greenPin,OUTPUT);

 
lcd.init(); //lcd calistirma
lcd.init();
lcd.backlight();
lcd.setCursor(0,1); // lcdye yazdırma konumu ayarı
lcd.print("   Kilit Sistemi   ");
lcd.setCursor(0,2);
lcd.print("                 ");
lcd.setCursor(0,3);
lcd.print("      ");
delay(3000);
lcd.clear();
LedRenk(true);
delay(20);
}

void loop()
{
  
  lcd.clear();
  lcd.print(" Sifreyi Giriniz: ");
  delay(100);
  
 char pressed=keypad.getKey();
 String key[3];
  
 if(pressed)
 {
  lcd.clear();
  lcd.print(" Sifreyi Giriniz: ");
  lcd.setCursor(position,2);
  lcd.print(pressed);
  delay(500);
    if(pressed == '*' || pressed == '#')
      {
          position = 0;
          LedRenk(true);
          lcd.clear();
      }

    else if(pressed == sifre[position])
      {
          key[position]=pressed;
          position++;
      }
 
    else if (pressed != sifre[position] )
      {
          wrong++;
          position ++;
      }

    if(position == 3){
          if( wrong >0)
            {
                total++;
                wrong = 0;
                position = 0;
                lcd.clear();
                lcd.setCursor(0,2);
                lcd.print("    Hatali Sifre!     ");
                delay(1000);
                LedRenk(true);
            }

          else if(position == 3 && wrong == 0)
            {
                position = 0;
                wrong = 0;
                lcd.clear();
                lcd.setCursor(0,1);
                lcd.print("      Hos geldiniz!     ");
                lcd.setCursor(5,2);
                lcd.print(" Kilit acildi.");
                delay(2000);
                LedRenk(false);
            }

             if(total ==3)
            {
                total=0;
               
                delay(500);
            }

        }

   }   
}

void LedRenk(int locked) // Hatalı ve doğru şifrede led değişimleri
  {
    if (locked)
      {
          digitalWrite(redPin, HIGH);
          digitalWrite(greenPin, LOW);
          delay(1000);
      }
    else
      {
          digitalWrite(redPin, LOW);
          digitalWrite(greenPin, HIGH);
          delay(2000);
          digitalWrite(redPin, HIGH);
          digitalWrite(greenPin, LOW);
      }
  }
