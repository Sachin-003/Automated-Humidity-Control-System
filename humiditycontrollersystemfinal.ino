#include <LiquidCrystal.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>


#define inc_btn 10
#define dec_btn 13
#define fan 8
#define humidifier_pin 9
#define DHTPIN 12 
#define DHTTYPE    DHT11

uint32_t delayMS;
int set_humidity = 50;
DHT_Unified dht(DHTPIN, DHTTYPE);
LiquidCrystal lcd(2,3,4,5,6,7);

void setup()
{
  lcd.begin(16,2);
  Serial.begin(9600);
  dht.begin();
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  delayMS = sensor.min_delay / 1000;
  pinMode(fan,OUTPUT);
  pinMode(humidifier_pin,OUTPUT);
  pinMode(inc_btn,INPUT);
  pinMode(dec_btn,INPUT);
 
}

void loop()
{
  delay(delayMS);
  sensors_event_t event;
  dht.humidity().getEvent(&event);
  int humidity = event.relative_humidity;
  Serial.print(F("Humidity: "));
  Serial.print(event.relative_humidity);
  Serial.println(F("%"));
  lcd.setCursor(0,0);
  lcd.clear();
  lcd.print("Humidity:");
  lcd.print(event.relative_humidity);
  lcd.print("%");
  int inc = digitalRead(inc_btn);
  int dec = digitalRead(dec_btn);
  if(inc == 1){
    set_humidity++;
    
  }
  if(dec == 1){
    set_humidity--;
  }
  lcd.setCursor(0,1);
  lcd.print("Set Humidity:");
  lcd.print(set_humidity);
  if(humidity>set_humidity){
    digitalWrite(fan,HIGH);
    digitalWrite(humidifier_pin,LOW);
  }
  else if(humidity<set_humidity){
    digitalWrite(humidifier_pin,HIGH);
    digitalWrite(fan,LOW);
  }
  else{
    digitalWrite(fan,LOW);
    digitalWrite(humidifier_pin,LOW);
  }
  Serial.print(F("Set Humidity: "));
  Serial.print(set_humidity);
  
  
}