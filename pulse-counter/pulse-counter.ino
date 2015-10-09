/*



*/

long count = 0;

const int A = 2;
//const int B = 3;

unsigned long time;
unsigned long nextTime;

long pulseTime= 0;

//------------------------------------------------------------------------------------------------------------------------------------

void setup()
{
  
  pinMode(A, INPUT);
 // pinMode(B, INPUT);
  
  attachInterrupt(0, pulse, RISING);
  //attachInterrupt(1, encoder_B, CHANGE);  
  
  Serial.begin(9800);
  
  time = millis();
  nextTime = time + 1000;
}

//-------------------------------------------------------------------------------------------------------------------------------------

void loop()
{
float diff = float(millis() - pulseTime);  

Serial.println(diff);
delay(50);
}

//-------------------------------------------------------------------------------------------------------------------------------------

void pulse()
{
	pulseTime = millis();
}