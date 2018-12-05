#include<SoftwareSerial.h>

long pmcf10 = 0;
long pmcf25 = 0;
long pmcf100 = 0;
long pmat10 = 0;
long pmat25 = 0;
long pmat100 = 0;
int count = 0;
unsigned char c, last_c;

const byte dataPin = 13;
const byte switchPin = 12;
const byte clockPin = 11;

const byte led = B01111111;

const byte LED7[10] = {
  B11001111,
  B00001001,
  B10100111,
  B10101101,
  B01101001,
  B11101100,
  B11101110,
  B11001001,
  B11101111,
  B11101001,
};

SoftwareSerial PMS(2,3);
SoftwareSerial BT(8,9);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Set up");
  BT.begin(9600);
  PMS.begin(9600);
  pinMode(dataPin,OUTPUT);
  pinMode(switchPin,OUTPUT);
  pinMode(clockPin,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned char high;
  while(PMS.available()){
    last_c = c;
    c = PMS.read();
    if(last_c == 0x42 && c == 0x4d) count = 1;
    if(count == 4 || count == 6 || count == 8 || count == 10 || count == 12 || count ==14)
      high = c;
    else if(count == 7){
      pmcf25 = 256 * high + c;
      Serial.print("CF = 1, PM25:");
      Serial.print(pmcf25);
      Serial.print("ug/m3");
      Serial.print("\n");
      BT.println(pmcf25);
      digitalWrite(switchPin,LOW);
      shiftOut(dataPin,clockPin,MSBFIRST,LED7[pmcf25/10]);
      shiftOut(dataPin,clockPin,MSBFIRST,LED7[pmcf25%10]);
      digitalWrite(switchPin,HIGH);
    }
    else if(count == 13){
      pmat25 = 256 * high + c;
//      Serial.print("atmosphere, PM25 = :");
//      Serial.print(pmat25);
//      Serial.print("ug/m3");
//      Serial.print("\n");
    }
    if(count < 100){
      count++;
    }
  }

}