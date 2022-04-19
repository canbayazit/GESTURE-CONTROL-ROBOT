#include <VirtualWire.h>
// motor one SAĞ MOTOR
int enA = 6; 
int in1 = 2;
int in2 = 3;
// motor two SOL MOTOR
int enB = 11;
int in3 = 4;
int in4 = 5;
const int datain = 12;
int hiz=70;
char c;
void setup()
{
    //Serial.begin(9600);
    vw_set_ptt_inverted(true);
    vw_set_rx_pin(datain);
    vw_setup(4000); 
    pinMode(enA, OUTPUT);
    pinMode(enB, OUTPUT);
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);
    vw_rx_start();
}
void sola_don()
{
        // SAĞ MOTOR İLERİ
       digitalWrite(in1,HIGH); 
       digitalWrite(in2,LOW);   
       // SOL MOTOR DUR     
       digitalWrite(in3,LOW); 
       digitalWrite(in4,LOW); 
       analogWrite(enA,hiz);    //arac sola dönecek .elin sola yatık olma durumu     
       analogWrite(enB,0);          
}
void saga_don()
{
       // SAĞ MOTOR DUR
       digitalWrite(in1,LOW); 
       digitalWrite(in2,LOW);        
       // SOL MOTOR İLERİ
       digitalWrite(in3,HIGH); 
       digitalWrite(in4,LOW); 
       analogWrite(enA,0);    //arac sola dönecek .elin sola yatık olma durumu
       analogWrite(enB,hiz);
}
void ileri_git()
{
      // SAĞ MOTOR İLERİ
       digitalWrite(in1,HIGH); 
       digitalWrite(in2,LOW);        
       // SOL MOTOR İLERİ
       digitalWrite(in3,HIGH); 
       digitalWrite(in4,LOW); 
       analogWrite(enA,hiz);    //arac sola dönecek .elin sola yatık olma durumu  
       analogWrite(enB,hiz);            
}
void geri_git()
{
  // SAĞ MOTOR GERİ
       digitalWrite(in1,LOW); 
       digitalWrite(in2,HIGH);        
       // SOL MOTOR GERİ
       digitalWrite(in3,LOW); 
       digitalWrite(in4,HIGH); 
       analogWrite(enA,hiz);    //arac sola dönecek .elin sola yatık olma durumu
       analogWrite(enB,hiz);            
}
void dur()
{
  // SAĞ MOTOR DUR
       digitalWrite(in1,LOW); 
       digitalWrite(in2,LOW);        
       // SOL MOTOR DUR
       digitalWrite(in3,LOW); 
       digitalWrite(in4,LOW); 
       analogWrite(enA,0);    //arac sola dönecek .elin sola yatık olma durumu
       analogWrite(enB,0);
}
void loop()
{
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;  
     //vw_get_message(buf,&buflen);
     //Serial.println(buf[0]);
    if (vw_get_message(buf,&buflen))
    {    
       c=char(buf[0]);    

         
          //Serial.println(c); 
    }
           if(String(c)=="B") // B bilgisi geldi ise el aşağıya
          {
            ileri_git();
          }
        else if(String(c)=="C") // C bilgisi geldi ise el yukarıya
          {
            geri_git();        
          }  
        else if(String(c)=="D") // D bilgisi geldi ise el sola yattı
          {
            sola_don();
          }
          else if(String(c)=="E") // E bilgisi geldi ise el sağa yattı
          {
            saga_don();
          }    
        else
        {
          dur();
        }
}
