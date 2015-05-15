/*

Velocity w/ Quadrature Encoder; Arduino w/ Interrupts
Author: Walter Coe
Date: 5/15/15
Affiliation: BYU Mechatronics Club

This code will read an quadrature encoder (two channels) via interrupts, count the total number of edges (rising and falling on
both channels). Every quarter second, the serial port will display the pulses-per-millisecond (clockwise positive), total pulse
count, and the time in milliseconds. For more informationon quarature encoders, see 
http://www.ni.com/white-paper/4763/en/

This code is by no means the most sophistocated or efficient. It serves as a basic starting place for learing to use encoders.

If less resolution is acceptable, an easy change to make is to comment out the interrupt attachent of either channel A or B 
(see lines 32-33).

*/

long count = 0;
long count_d1;

const int A = 2;
const int B = 3;

unsigned long time_d1;
unsigned long time;
unsigned long nextTime;

float rate;
float rate_d1;

//----------------------------------------------------------------------------------------------------------------------------

void setup()
{
  
  pinMode(A, INPUT);
  pinMode(B, INPUT);
  
  attachInterrupt(0, encoder_A, CHANGE);
  attachInterrupt(1, encoder_B, CHANGE);  
  
  Serial.begin(9800);
  
  time_d1 = millis();
  time = millis();
  nextTime = time + 1000;
  
  rate_d1 = 0;
  
}

//============================================================================================================================

void loop()
{
  
  Serial.print(rate,4);
  Serial.print("\t");
  Serial.print(count);
  Serial.print("\t");
  Serial.println(millis());
  
  while(time < nextTime)
  {
     
    time = millis();
    rate = velocity(count, count_d1, time, time_d1, rate_d1);
    count_d1 = count;
    time_d1 = millis();
    rate_d1 = rate;
    
    delay(10);  //delay .01 seconds
         
  }
  
  nextTime = time + 250;
}

//============================================================================================================================

void encoder_A()
{
  int As = digitalRead(A);
  int Bs = digitalRead(B);
 
 if(As==HIGH)
 {
    if(Bs==HIGH)
    {
      count = count - 1;
    }
    else
    {
      count = count + 1; 
    }
 }
 else
 {
   if(Bs==HIGH)
    {
      count = count + 1;
    }
    else
    {
      count = count - 1; 
    }
 }
 
}

//----------------------------------------

void encoder_B()
{
     
 int As = digitalRead(A);
 int Bs = digitalRead(B);
 
 if(Bs==HIGH)
 {
    if(As==HIGH)
    {
      count = count + 1;
    }
    else
    {
      count = count - 1; 
    }
 }
 else
 {
   if(As==HIGH)
    {
      count = count - 1;
    }
    else
    {
      count = count + 1; 
    }
 }
 }

//----------------------------------------

float velocity(long countNow, long countLast, unsigned long now, unsigned long last, float lastVel)
{
  
    float vel;
    float tau = 1.50;  //used for digital low-pass filtering
    
    vel = (((float)(countNow - countLast)*2.0)/((float)(now - last) + 2.0*tau)) + (2*tau - ((float)(now - last)))/(2*tau+(float)(now - last))*lastVel;
    
    return(vel);
  
}



