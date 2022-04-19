#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include <VirtualWire.h>

const int ledPin = 9;
char *data;
/* Assign a unique ID to this sensor at the same time */
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

/*
void SensorDetaylari(void)
{
  sensor_t sensor;
  accel.getSensor(&sensor);
  Serial.println("------------SENSOR DETAYLARIMIZ----------");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Surucu Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Benzersiz ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Deger:    "); Serial.print(sensor.max_value); Serial.println(" m/s^2");
  Serial.print  ("Min Deger:    "); Serial.print(sensor.min_value); Serial.println(" m/s^2");
  Serial.print  ("Cozunurluk:   "); Serial.print(sensor.resolution); Serial.println(" m/s^2");  
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
}
*/
void setup(void) 
{
  //Serial.begin(9600);  
  /* Sensorun durumuna bakılıyor. */
 if(!accel.begin())
  {
   // Serial.println("Dikkat!ADXL345 Bulunamadi ... Kablolari kontrol ediniz!");
    while(1);
  }
  //SensorDetaylari();
  pinMode(ledPin,OUTPUT);
  vw_set_ptt_inverted(true);
  vw_set_tx_pin(12);
  vw_setup(4000);//2000
  //Serial.println();
}

void loop(void) 
{
  
  /* yeni sensor olayı alınıyor */ 
  
  sensors_event_t event; 
  accel.getEvent(&event);
 

 // Serial.print("X: "); Serial.print(event.acceleration.x); Serial.print("  ");
 // Serial.print("Y: "); Serial.print(event.acceleration.y); Serial.println("  ");
  if(event.acceleration.x>-5 && event.acceleration.x<4 && event.acceleration.y>-3 && event.acceleration.y<4) //elimiz düz ise
    data="A"; // DUR 65
  else if(event.acceleration.x<-5 && event.acceleration.y>-3 && event.acceleration.y<4)// && event.acceleration.y>-2 && event.acceleration.y<2)
    data="E"; // SAĞA DÖN 69
  else if(event.acceleration.x>4 && event.acceleration.y>-3 && event.acceleration.y<4)// && event.acceleration.y>-2 && event.acceleration.y<2)
    data="D"; // SOLA DÖN 68
  else if(event.acceleration.x>-5 && event.acceleration.x<4 && event.acceleration.y<-3)
    data="B"; //İLERİ 66
  else if(event.acceleration.x>-5 && event.acceleration.x<4 && event.acceleration.y>4)
    data="C"; //GERİ  67
  else 
    data="A"; 
  //Serial.println(data);
  vw_send((uint8_t *)data, strlen(data));
  vw_wait_tx(); 
  digitalWrite(ledPin,HIGH);
  delay(200);
 /* data="0";
  vw_send((uint8_t *)data, strlen(data));
  vw_wait_tx();*/
  digitalWrite(ledPin,LOW);
  delay(200);
}
