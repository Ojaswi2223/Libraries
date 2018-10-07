#include <BotBase.h>
#include <D45Base.h>

int D45BASE_DIRs[] = {47, 53, 51, 49};
int D45BASE_PWMs[] = {8, 10, 9, 7};
bool D45BASE_REVs[] = {false, false, true, true};

D45Base robotBase;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
  robotBase.Initialize("FWS_1", &Serial, 0);
  robotBase.AssignPins(D45BASE_PWMs, D45BASE_DIRs, D45BASE_REVs);
  Serial.println("Going into loop ....");
}

int pwm = 0;
float angle = 0;

void loop() {
  // put your main code here, to run repeatedly:
  robotBase.Move(pwm, angle);
  //robotBase.Move(100,180);
  while (Serial.available()) {
    char c = Serial.read();
    if (c == 'P') {
      Serial.println("'P' (PWM) received");
      int val = Serial.parseInt();
      Serial.print(val);
      Serial.println(" received");
      pwm = val;
    }
    else if (c == 'A') {
      Serial.println("'A' (angle) received");
      int val = Serial.parseInt();
      Serial.print(val);
      Serial.println(" received");
      angle = val;
    }
    else if (c == 'C')
    {
      Serial.println(" Clockwise rotation command received ");
      int val = Serial.parseInt();
      Serial.print(val);
      pwm = val;
      robotBase.Rotate(-pwm);
    }
    else if (c == 'R')
    {
      Serial.println(" Anti-Clockwise rotation command received ");
      int val = Serial.parseInt();
      Serial.print(val);
      pwm = val;
      robotBase.Rotate(pwm);
    }
    else if (c == 'K')
    {
      Serial.println("Killed all motors");
      robotBase.KillMotors();
    }
  }
}
