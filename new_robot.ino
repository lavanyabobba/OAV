// #include "ESP8266_AT.h"
//MOTOR1 PINS
#define l_ir A3

#define mid_ir A4
#define r_ir A5
int ena = 3;
int in1 = 6;
int in2 = 7;
int enb = 11;
int in3 = 10;
int in4 = 9;
int mtrig=2;
int mecho=4;
int side_trig=5;
int side_echo=8;
long mtimeInMicro;
long mdistanceINCm;
long rtimeInMicro;
long rdistanceINCm;
long ltimeInMicro;
long ldistanceINCm;
int x=0;
int y=0;
int reading;
int BUZ=12;
int hd_light= A2;
int val1=10000;
int val2=8000;
int val3=6000;
long msens()
{
digitalWrite(mtrig,LOW);
delayMicroseconds(100);
digitalWrite(mtrig,HIGH);
delayMicroseconds(100);
digitalWrite(mtrig,LOW);
mtimeInMicro=pulseIn(mecho,HIGH);
mdistanceINCm=mtimeInMicro/29/2;
delay(10);
return mdistanceINCm;
}
long rsens()
{
digitalWrite(side_trig,LOW);
delayMicroseconds(100);
digitalWrite(side_trig,HIGH);
delayMicroseconds(100);
digitalWrite(side_trig,LOW);
rtimeInMicro=pulseIn(side_echo,HIGH);
rdistanceINCm=rtimeInMicro/29/2;
return rdistanceINCm;
delay(10);
}
void forward()
{
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  analogWrite(enb, 95);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  analogWrite(ena, 95);
  // delay(2000);  
}
void stop()
{
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  analogWrite(ena, 70);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
  analogWrite(enb, 70);  
  delay(1000);
}
void horn(int val)
{
  tone(BUZ, val);
  delay(500);
  noTone(BUZ);
  delay(500);
}
void rev()
{
  delay(500);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  analogWrite(ena, 100);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
  analogWrite(enb, 70);
   if(digitalRead(l_ir)==LOW)
  {
    stop();
  }
  else if(digitalRead(mid_ir)==LOW)
  {
  stop();
  }
  else if(digitalRead(r_ir)==LOW)
  {
  stop();
  }
}
void left()
{
  // stop();
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  analogWrite(ena, 150);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
  analogWrite(enb, 70);  
  delay(500);
}
void right()
{
  // delay(1000);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  analogWrite(ena, 150);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  analogWrite(enb, 70);  
  delay(500);
}
void blink()
{
digitalWrite(hd_light,HIGH);
delay(250); 
}
void setup()
{
  Serial.begin(9600);
  pinMode(ena, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enb, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(mtrig,OUTPUT);
  pinMode(mecho,INPUT);
  pinMode(side_trig,OUTPUT);
  pinMode(side_echo,INPUT);
  pinMode(BUZ,OUTPUT);
  pinMode(hd_light,OUTPUT);  
}  
void loop() 
{  
  int True=1;
  forward();
  while(True)
  {
  // forward();  
  x=msens();
  y=rsens();  
  Serial.print("Mid Data: ");
  Serial.println(x);
  Serial.print("Nearest Data: ");
  Serial.println(y);
  blink();  
  if(x>=100 && y>=90)
  {
    Serial.println("GOTO START");
    forward();
    blink();
  } 
  else
  { 
     if((x>=60) && (y>=50))  
     {
       Serial.println("GOTO AVOID P1");
        forward();
        horn(val3); 
        break;
     }
    
   else if((x>=50) && (y>=45))
    {
      Serial.println("GOTO AVOID P2");
      forward();
      horn(val2);
    }  
   else if((x>=20) && (y>=15))
    {
       Serial.println("GOTO AVOID P3");
      horn(val1);
      left();
      if(y<35)
      {
        rev();
        right();
      }
      else
      {
        forward();
        right();
      }
      // stop();
    } 
    else
    {
     rev();
    }       
      // stop(); 
      // // rev(); 
      // // left();
      // // right(); 
}
}
}