//Termometre kod
# include "LiquidCrystal.h"         
const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7; // lcd bağlantılarımız
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
float gecici;          // lm35 icin tmp deger

void setup() {          //system kurumu
  Serial.begin(9600);
  analogReference(2);
  lcd.begin (16,2);                    // burada yazdıgım kodlar programıin bir kere calismasi icindir
  lcd.setCursor(0, 0);
  lcd.print(" Thermometer ");      
  lcd.setCursor(0, 1);  // lcd yazdırma işleminde alt satıra geçmek için
  delay(400);
  lcd.print(" V2.0  ");
  delay (700);
  lcd.clear();                                           
}
void loop() {
  gecici = analogRead(A0);                                                    //temp = temp * 0.48828125;  //temp=temp*(5.0/1023.0)*100; sicaklik hesabi formulu
  gecici=gecici*1100/(1024*10);
  lcd.print("TEMP: ");
  lcd.print(gecici);
  lcd.print("*C");
  lcd.setCursor(0, 1);
  if(gecici<20){ // 20 dereceden düşükse
    lcd.println("Sicaklik dustu");
  }
  if(30<gecici) // 30 dereceden yüksekse
  {
    lcd.println("Sicaklik yukseldi"); 
  }
  
  
  delay(500);
  lcd.clear();                                           //system kurulumu
}
