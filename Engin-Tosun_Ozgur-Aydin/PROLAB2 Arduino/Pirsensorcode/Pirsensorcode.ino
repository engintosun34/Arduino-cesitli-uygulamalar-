int kalibrasyonZamani = 10; //Sensorun hazirlanmasi icin verdigim zaman 
long unsigned int hghlow; //tüm hareketin durduğunu varsaymadan önce sensörün milisaniye miktarının düşük olması gerekir
long unsigned int pause = 5000; 
boolean lockLow = true; 
boolean gecikme; 
int pirPin = 3; //digital pine bağlantı pir sensoru icin
int lampPin = 13; //led 13 e baaglı

void setup()
{
  Serial.begin(9600); 
  pinMode(pirPin, INPUT); 
  pinMode(lampPin, OUTPUT); 
  digitalWrite(pirPin, LOW); //sensore kalibre icin zaman
  Serial.print("Sensor Hazirlaniyor "); 
  for(int i = 0; i <kalibrasyonZamani ; i++)
  { 
    Serial.print("."); 
    delay(1000); 
  } 
  
  Serial.println(" done"); 
  Serial.println("SENSOR AKTIF"); 
  delay(50); 
} 
  
void loop()
{   
  if(digitalRead(pirPin) == HIGH)    
  {      
    digitalWrite(lampPin, HIGH); //led, sensörlerin çıkış pin durumunu görselleştirir
    
    if(lockLow)      
    { //daha fazla çıktı yapılmadan önce DÜŞÜK'e geçişi beklediğimizden emin olur:        
      lockLow = false; 
      Serial.println("---");        
      Serial.print("hareket algilandi= "); 
      Serial.print(millis()/1000); 
      Serial.println(" sn"); 
      delay(50);      
    } 
    gecikme = true; 
  } 
    
  if(digitalRead(pirPin) == LOW)    
  {       
    digitalWrite(lampPin, LOW); //led, sensörlerin çıkış pin durumunu görselleştirir
    
    if(gecikme)      
    {         
      hghlow = millis(); //yüksekten DÜŞÜK'e geçiş zamanından tasarruf edin     
      gecikme = false; //bunun yalnızca DÜŞÜK aşamanın başlangıcında yapıldığından emin olun     
    } //sensör verilen duraklamadan daha uzun süre düşükse, daha fazla hareket olmayacağını varsayıyoruz   
    
    if(!lockLow && millis() - hghlow > pause)          
    { //bu kod bloğunun yalnızca yeni bir hareket dizisi algılandıktan sonra yeniden yürütülmesini sağlar
      lockLow = true; 
      Serial.print("hareket durdu= "); //çıktı        
      Serial.print((millis() - pause)/1000);          
      Serial.println(" sn"); delay(50);       
    } 
  } 
}
  
