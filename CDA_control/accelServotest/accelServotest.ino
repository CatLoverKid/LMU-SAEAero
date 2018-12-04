#include <Wire.h>
#include <LSM6.h>
#include <Servo.h>

Servo aero;
LSM6 imu;

float ACC_CONVERSION_FACTOR = 0.000061;
float GRYO_CONVERSION_FACTOR = 0.001;
int AERO_PIN = 8;

char report[80];
int servoPos;

void setup()
{
  aero.attach(AERO_PIN);
  Serial.begin(9600);
  Wire.begin();
  
  if (!imu.init())
  {
    Serial.println("Failed to detect and initialize IMU!");
    while (1);
  }
  imu.enableDefault();
}

void loop()
{
  imu.read();
  
  float ax = imu.a.x * ACC_CONVERSION_FACTOR;
  float ay = imu.a.y * ACC_CONVERSION_FACTOR;
  float az = imu.a.z * ACC_CONVERSION_FACTOR;
  
  float gx = imu.g.x * GRYO_CONVERSION_FACTOR;
  float gy = imu.g.y * GRYO_CONVERSION_FACTOR;
  float gz = imu.g.z * GRYO_CONVERSION_FACTOR;
  
  //Serial.println("A: " + (String)ax + ", " + (String)ay + ", " + (String)az + " G: " + (String)gx + ", " + (String)gy + ", " + (String)gz);
  Serial.println((int)floor(constrain((ay * 90) + 90, 30, 150)));
  aero.write((int)floor(constrain((ay * 90) + 90, 30, 150)));
  delay(100);
}
