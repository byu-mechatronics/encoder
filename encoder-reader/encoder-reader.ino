/*

Basic Quadrature Encoder; Arduino w/ Interrupts
Author: Walter Coe
Date: 5/12/15
Affiliation: BYU Mechatronics Club

This code will read an quadrature encoder (two channels) via interrupts, count the total number of edges (rising and falling
on both channels). Every second, the serial port will display the net pulse count (clockwise positive). For more information
on quarature encoders, see 
http://www.ni.com/white-paper/4763/en/

If less resolution is acceptable, an easy change to make is to comment out the interrupt attachent of either channel A or B
(see lines 32-33).

*/

long count = 0;

const int A = 2;
const int B = 3;

unsigned long time;
unsigned long nextTime;

//------------------------------------------------------------------------------------------------------------------------------------

void setup()
{
  
  pinMode(A, INPUT);
  pinMode(B, INPUT);
  
  attachInterrupt(0, encoder_A, CHANGE);
  attachInterrupt(1, encoder_B, CHANGE);  
  
  Serial.begin(9800);
  
  time = millis();
  nextTime = time + 1000;
}

//-------------------------------------------------------------------------------------------------------------------------------------

void loop()
{
  

  Serial.println(count);
  
  while(time < nextTime)
  {
     time = millis(); 
  }
  
  nextTime = time + 1000;
}

//-------------------------------------------------------------------------------------------------------------------------------------

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

//-------------------------------------------------------------------------------------

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


