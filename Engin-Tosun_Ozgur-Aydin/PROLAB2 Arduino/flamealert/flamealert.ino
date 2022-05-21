#define FlamePin A0 //yangın sensörü pini girişi
#define buzzer 1 //buzzer pini

void setup() {   // kurulum
   
   pinMode(FlamePin, INPUT); 
   pinMode(buzzer, OUTPUT);
    
   delay(10);  
}

void loop() { // calisma mekanizmasi

int Flame = digitalRead(FlamePin);

if(Flame==HIGH) //Yangın high verirse
{
  digitalWrite(buzzer, HIGH); //buzzerın çalışması uyarılır.
  delay(10);
  
}
else
{
 digitalWrite(buzzer, LOW); //diger durumda çalışmaz
}
  
} 
