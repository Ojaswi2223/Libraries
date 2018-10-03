#include <LSA08.h>

LSA08 lsa;
void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
    Serial2.begin(38400);
    lsa.Initialize('s', 1,0,&Serial2);

}

void loop() {
  // put your main code here, to run repeatedly:
int val = lsa.ReadLSA(0);
Serial.println(val);
nt flag= lsa.LSA_Flag;
Serial.println(flag);
}
