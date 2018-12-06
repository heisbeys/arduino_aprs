#include <math.h>

const char samplePoints=20;
int dacLookTable[samplePoints];
const float pi=3.141592;
const int dacBias=2048;
const int dacAmpl=4000;
const float freqAdj=1.2;
const int freq=1200;

int calcDACLookTable(int point)
{
  dacLookTable[0] = (int)(dacBias + (0.5 * dacAmpl * sin(2*pi*point/samplePoints)));
}

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  analogWriteResolution(12);
  Serial.begin(9600);

  for(int i=0;i<samplePoints;i++)
    dacLookTable[i]=calcDACLookTable(i+1);
    
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i=0;i<samplePoints;i++)
  {
    digitalWrite(LED_BUILTIN,HIGH);
    analogWrite(DAC1, dacLookTable[i]);
    delayMicroseconds(1000000/(freq*freqAdj*samplePoints));
    digitalWrite(LED_BUILTIN,LOW);
  }
}