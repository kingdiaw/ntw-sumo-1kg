#include "CytronMotorDriver.h"


// Configure the motor driver.
CytronMD motor_left(PWM_DIR, 3, 4);    // PWM 1 = Pin 3, DIR 1 = Pin 4.
CytronMD motor_right(PWM_DIR, 9, 10);  // PWM 2 = Pin 9, DIR 2 = Pin 10.

//CH1 - TH
const byte CH1 = 13; 
//CH2 - ST
const byte CH2 = 2;
//UNUSE
const byte CH3 = 6;

//CH1 - TH
const int Y_MIN = 999;  // ch1
const int Y_MAX = 2031;
//CH2 - ST
const int X_MIN = 1000;  //ch2
const int X_MAX = 2000;
const int Z_MIN = 999;
const int Z_MAX = 2031;

byte receiver_pinArray[] = { CH1, CH2, CH3 };

int ch1;
int ch2;
int y;
int x;
int z;
int strength;
int angle;
int special;
int enable;
int16_t g;
// The setup routine runs once when you press reset.
void setup() {
  Serial.begin(115200);
  for (byte i = 0; i < sizeof(receiver_pinArray); i++) {
    pinMode(receiver_pinArray[i], INPUT);
  }
}


// The loop routine runs over and over again forever.
void loop() {
  y = pulseIn(CH1, HIGH, 25000);
  x = pulseIn(CH2, HIGH, 25000);  //angle
  z = pulseIn(CH3, HIGH, 25000);
  strength = map(y, Y_MAX, Y_MIN, -100, 100);
  angle = map(x, X_MIN, X_MAX, 0, 180);
  special = map(z, Z_MIN, Z_MAX, 0, 100);

  angle = abs(angle);
  if (strength > 100) strength = 100;
  if (strength < -100) strength = -100;

  /*
    Serial.print("Strength:");
    Serial.println(strength);
    Serial.print("angle:");
    Serial.println(angle);
  */

  if (strength > 5) {  //forward 5
    if (angle > 90)    //turn right >90
    {
      robot(1, 1, (strength * ((180 - angle) * 255 / 90) / 100), (strength * 255 / 100)); 
    } else if (angle < 90)  //turn left <90 1,1,
    {
      robot(1, 1, (strength * 255 / 100), (strength * (angle * 255 / 90)) / 100);  //1,1
    }
  } else if (strength < -5) {  //-5
    if (angle > 90)            //turn right >90
    {
      robot(0, 0, (abs(strength) * 255 / 100), (abs(strength) * ((180 - angle) * 255 / 90) / 100));
    } else if (angle < 90)  //turn left <90 0,0
    {
      robot(0, 0, (abs(strength) * (angle * 255 / 90)) / 100, (abs(strength) * 255 / 100));  //0,0
    }
  } else {
    robot(1, 1, 0, 0);  //1100
  }
}
void robot(uint8_t mL, uint8_t mR, uint8_t speedL, uint8_t speedR) {
  if (mL > 0) {  //motor left forward
    int16_t speed = speedL;
    motor_left.setSpeed(speed);
  } else {  //motor left backward
    int16_t speed = speedL * -1;
    motor_left.setSpeed(speed);
  }
  if (mR > 0) {  //motor left forward
    int16_t speed = speedR * -1;
    motor_right.setSpeed(speed);
  } else {  //motor left backward
    int16_t speed = speedR;
    motor_right.setSpeed(speed);
  }
}
