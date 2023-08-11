//////////////////////////////////////////////
//        RemoteXY include library          //
//////////////////////////////////////////////

// RemoteXY select connection mode and include library 
#define REMOTEXY_MODE__ESP8266_HARDSERIAL_POINT

#include <RemoteXY.h>

// RemoteXY connection settings 
#define REMOTEXY_SERIAL Serial
#define REMOTEXY_SERIAL_SPEED 115200
#define REMOTEXY_WIFI_SSID "RemoteXY"
#define REMOTEXY_WIFI_PASSWORD "12345678"
#define REMOTEXY_SERVER_PORT 6377


// RemoteXY configurate  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =   // 242 bytes
  { 255,8,0,22,0,235,0,16,24,0,2,0,5,20,15,6,1,26,31,31,
  79,78,0,79,70,70,0,2,0,25,20,15,6,1,26,31,31,79,78,0,
  79,70,70,0,5,33,65,30,30,30,1,16,31,1,0,6,42,15,15,1,
  31,72,79,82,78,0,10,48,25,42,15,15,12,1,31,77,79,68,69,0,
  31,79,70,70,0,10,49,5,30,15,6,50,135,31,76,69,70,84,0,31,
  79,70,70,0,10,49,25,30,15,6,50,135,31,82,73,71,72,84,0,31,
  79,70,70,0,129,0,6,16,13,2,16,76,69,70,84,32,77,79,84,79,
  82,0,129,0,25,16,14,2,16,82,73,71,72,84,32,77,79,84,79,82,
  0,67,4,52,6,42,5,24,16,11,67,4,5,6,43,5,24,16,11,129,
  0,52,2,41,3,16,78,69,65,82,69,83,84,32,77,73,68,32,83,69,
  78,83,79,82,32,68,65,84,65,0,129,0,5,2,43,3,16,78,69,65,
  82,69,83,84,32,83,73,68,69,32,83,69,78,83,79,82,32,68,65,84,
  65,0 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // input variables
  uint8_t switch_1; // =1 if switch ON and =0 if OFF 
  uint8_t switch_2; // =1 if switch ON and =0 if OFF 
  int8_t joystick_1_x; // from -100 to 100  
  int8_t joystick_1_y; // from -100 to 100  
  uint8_t button_1; // =1 if button pressed, else =0 
  uint8_t mode; // =1 if state is ON, else =0 
  uint8_t l_light; // =1 if state is ON, else =0 
  uint8_t r_light; // =1 if state is ON, else =0 
  
    // output variables
  char msd[11];  // string UTF8 end zero 
  char ssd[11];  // string UTF8 end zero 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////


#define PIN_SWITCH_1 3
#define PIN_SWITCH_2 11
#define PIN_BUTTON_1 12
#define PIN_MODE 13
#define PIN_L_LIGHT A0
#define PIN_R_LIGHT A1
//define right motor control pins
#define right_motor_A 6
#define right_motor_B 7
#define right_motor_speed 3 //enable pin

//define left motor control pins
#define left_motor_A 10
#define left_motor_B 9
#define left_motor_speed 11 //enable pin
#define hd_light A2

//define two arrays with a list of pins for each motor
uint8_t RightMotor[3] = {right_motor_A, right_motor_B, right_motor_speed};
uint8_t LeftMotor[3] = {left_motor_A, left_motor_B, left_motor_speed};
//auto mode
#define l_ir A3
#define mid_ir A4
#define r_ir A5
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
int val1=10000;
int val2=8000;
int val3=6000;
int r_light=A1;
int l_light=A0;
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
  dtostrf(x,0,1,RemoteXY.msd);
  dtostrf(y,0,1,RemoteXY.ssd);
  digitalWrite(left_motor_A,HIGH);
  digitalWrite(left_motor_B,LOW);
  analogWrite(left_motor_speed, 95);
  digitalWrite(right_motor_A,HIGH);
  digitalWrite(right_motor_B,LOW);
  analogWrite(right_motor_speed, 95);

  // delay(2000);  
}
void stop()
{
  digitalWrite(right_motor_A,LOW);
  digitalWrite(right_motor_B,LOW);
  analogWrite(right_motor_speed, 70);
  digitalWrite(left_motor_A,LOW);
  digitalWrite(left_motor_B,LOW);
  analogWrite(left_motor_speed, 70);  
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
  dtostrf(x,0,1,RemoteXY.msd);
  dtostrf(y,0,1,RemoteXY.ssd);
  delay(500);
  digitalWrite(right_motor_A,LOW);
  digitalWrite(right_motor_B,HIGH);
  analogWrite(right_motor_speed, 100);
  digitalWrite(left_motor_A,LOW);
  digitalWrite(left_motor_B,HIGH);
  analogWrite(left_motor_speed, 70);
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
void a_rev()
{
  delay(500);
  digitalWrite(right_motor_A,LOW);
  digitalWrite(right_motor_B,HIGH);
  analogWrite(right_motor_speed, 255);
  digitalWrite(left_motor_A,LOW);
  digitalWrite(left_motor_B,HIGH);
  analogWrite(left_motor_speed, 255);
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
  digitalWrite(right_motor_A,HIGH);
  digitalWrite(right_motor_B,LOW);
  analogWrite(right_motor_speed, 150);
  digitalWrite(left_motor_A,LOW);
  digitalWrite(left_motor_B,LOW);
  analogWrite(left_motor_speed, 70);  
  delay(500);
  dtostrf(x,0,1,RemoteXY.msd);
  dtostrf(y,0,1,RemoteXY.ssd);
}
void right()
{
  // delay(1000);
  digitalWrite(right_motor_A,LOW);
  digitalWrite(right_motor_B,HIGH);
  analogWrite(right_motor_speed, 150);
  digitalWrite(left_motor_A,HIGH);
  digitalWrite(left_motor_B,LOW);
  analogWrite(left_motor_speed, 70);  
  delay(250);
   dtostrf(x,0,1,RemoteXY.msd);
   dtostrf(y,0,1,RemoteXY.ssd);
}
void blink()
{
digitalWrite(hd_light,HIGH);
delay(250); 
}
void r_blink()
{
   digitalWrite(r_light,HIGH);
  delay(250);
  digitalWrite(r_light,LOW);
  delay(250);
   digitalWrite(r_light,HIGH);
  delay(250);
  digitalWrite(r_light,LOW);
  delay(250);
}
void l_blink()
{
  digitalWrite(l_light,HIGH);
  delay(250);
  digitalWrite(l_light,LOW);
  delay(250);
   digitalWrite(l_light,HIGH);
  delay(250);
  digitalWrite(l_light,LOW);
  delay(250);
}
//speed control of motors
void Wheel (uint8_t * motor, int v) // v = motor speed, motor = pointer to an array of pins 
{
  if (v > 100) v=100;
  if (v < -100) v=-100;
  if (v > 0)
  {

    digitalWrite (motor [0], HIGH);
    digitalWrite (motor [1], LOW);
    analogWrite (motor [2], v * 2.55);
  }
  else if ( v<0 ){

    digitalWrite (motor [0], LOW);
    digitalWrite (motor [1], HIGH);
    analogWrite (motor [2], (-v) * 2.55);
  }
  else
  {
    digitalWrite (motor [0], LOW);
    digitalWrite (motor [1], LOW);
    analogWrite (motor [2], 0);
  }
}

void setup() 
{
  RemoteXY_Init (); 
  
  pinMode (PIN_SWITCH_1, OUTPUT);
  pinMode (PIN_SWITCH_2, OUTPUT);
  pinMode (PIN_BUTTON_1, OUTPUT);
  pinMode (PIN_MODE, OUTPUT);
  pinMode (PIN_L_LIGHT, OUTPUT);
  pinMode (PIN_R_LIGHT, OUTPUT);
  // TODO you setup code
  pinMode (right_motor_A, OUTPUT);
  pinMode (right_motor_B, OUTPUT);
  pinMode (left_motor_A, OUTPUT);
  pinMode (left_motor_B, OUTPUT);
  pinMode(hd_light,OUTPUT);
  pinMode(mtrig,OUTPUT);
  pinMode(mecho,INPUT);
  pinMode(side_trig,OUTPUT);
  pinMode(side_echo,INPUT);
  pinMode(r_light,OUTPUT);
  pinMode(l_light,OUTPUT);
}

void loop() 
{ 
  x=msens();
  y=rsens(); 
  dtostrf(x,0,1,RemoteXY.msd);
  dtostrf(y,0,1,RemoteXY.ssd); 
  digitalWrite(hd_light,HIGH);
  RemoteXY_Handler ();
  // TODO you loop code
  // use the RemoteXY structure for data transfer
  // do not call delay() 
  if(RemoteXY.mode==1)
  {
    RemoteXY_Handler ();
    int True=1;
    forward();
    while(True)
    {
      RemoteXY_Handler ();
      x=msens();
      y=rsens();
      dtostrf(x,0,1,RemoteXY.msd);
      dtostrf(y,0,1,RemoteXY.ssd); 
      // forward();  
      Serial.print("Mid Data: ");
      Serial.println(x);
      Serial.print("Nearest Data: ");
      Serial.println(y);
      blink();  
      if(x>=100 && y>=90)
      {
      dtostrf(x,0,1,RemoteXY.msd);
      dtostrf(y,0,1,RemoteXY.ssd); 
      Serial.println("GOTO START");
      forward();
      blink();
      } 
      else
      { 
        dtostrf(x,0,1,RemoteXY.msd);
        dtostrf(y,0,1,RemoteXY.ssd);
        if((x>=60) && (y>=50))  
        {
          dtostrf(x,0,1,RemoteXY.msd);
          dtostrf(y,0,1,RemoteXY.ssd);
          Serial.println("GOTO AVOID P1");
          forward();
          horn(val3); 
          break;
        }
    
        else if((x>=50) && (y>=45))
        {
          dtostrf(x,0,1,RemoteXY.msd);
          dtostrf(y,0,1,RemoteXY.ssd);
          Serial.println("GOTO AVOID P2");
          forward();
          horn(val2);
          break;
        }  
        else if((x>=20) && (y>=15))
        {
          dtostrf(x,0,1,RemoteXY.msd);
          dtostrf(y,0,1,RemoteXY.ssd);
          Serial.println("GOTO AVOID P3");
          horn(val1);
          l_blink();
          left();
          if(y<35)
           {
             dtostrf(x,0,1,RemoteXY.msd);
            dtostrf(y,0,1,RemoteXY.ssd);
            r_blink();
            rev();
            right();
          }
          else
          {
            dtostrf(x,0,1,RemoteXY.msd);
            dtostrf(y,0,1,RemoteXY.ssd);
            l_blink();
            forward();
            right();
          }
          // stop();
        } 
        else
        {
          dtostrf(x,0,1,RemoteXY.msd);
          dtostrf(y,0,1,RemoteXY.ssd);
          rev();
        }       
        // stop(); 
        // // rev(); 
        // // left();
        // // right(); 
      }
    }
  }
 else if(RemoteXY.mode==0)
  {
    RemoteXY_Handler ();
    x=msens();
    y=rsens(); 
    digitalWrite(PIN_SWITCH_1, (RemoteXY.switch_1==0)?LOW:HIGH);
    digitalWrite(PIN_SWITCH_2, (RemoteXY.switch_2==0)?LOW:HIGH);
    digitalWrite(PIN_BUTTON_1, (RemoteXY.button_1==0)?LOW:HIGH);
    digitalWrite(PIN_MODE, (RemoteXY.mode==0)?LOW:HIGH);
    Wheel (RightMotor, RemoteXY.joystick_1_y - RemoteXY.joystick_1_x);
    Wheel (LeftMotor, RemoteXY.joystick_1_y + RemoteXY.joystick_1_x);
    digitalWrite(PIN_L_LIGHT, (RemoteXY.l_light==0)?LOW:HIGH);
    digitalWrite(PIN_R_LIGHT, (RemoteXY.r_light==0)?LOW:HIGH);
    if((x<=30) || (y<=25))
    {
      horn(val1);
      a_rev();
    }
    // dtostrf(x,0,1,RemoteXY.msd);
    // dtostrf(y,0,1,RemoteXY.ssd);
  }
}