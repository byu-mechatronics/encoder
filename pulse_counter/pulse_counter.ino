/*



*/

long count = 0;

const int A = 2;
//const int B = 3;

unsigned long time;
unsigned long nextTime;

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
  

  Serial.println(count);
  
  while(time < nextTime)
  {
     time = millis(); 
  }
  
  nextTime = time + 1000;
}

//-------------------------------------------------------------------------------------------------------------------------------------

void pulse()
{
	count = count + 1;
}