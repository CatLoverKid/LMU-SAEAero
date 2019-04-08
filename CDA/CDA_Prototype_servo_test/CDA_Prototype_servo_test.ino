#include <Wire.h>
#include <LSM6.h>
#include <Servo.h>
#include <SoftwareSerial.h>
#include <Adafruit_GPS.h>

// Constants
#define ACCEL_CONVERSION_FACTOR 0.000061
#define GRYO_CONVERSION_FACTOR 0.001
#define SERVO_DEAD_ZONE 10

// Defining Pinouts
#define IMU_SDA_PIN "A5" // Changing SDA/SCL will require rewrite of code to support custom Wire Instance
#define IMU_SCL_PIN "A4" // See note for IMU_SDA_PIN, definition only here for hardware reference
#define AERO_R_PIN 6
#define AERO_L_PIN 5

// etc helpers constants
#define LINE_BREAK "***********************************************"
#define DEBUG_MODE true

Servo aeroR;
Servo aeroL;
LSM6 IMU;

void setup() {
  Serial.begin(115200);
  Serial.println(LINE_BREAK);
  Serial.println("LMU SAE Aero Basic Demonstration and Test");
  Serial.println(LINE_BREAK);

  Wire.begin(); // IMU uses Wire, which by default uses SDA and SCL on the Arduino (A4 and A5)
  if (!IMU.init() && DEBUG_MODE) {
    Serial.println("Failed to detect and initialize IMU!");
    Serial.println("Exiting");
    while (1);
  }
  IMU.enableDefault();

  // Initialize Servo motors
  aeroR.attach(AERO_R_PIN);
  aeroL.attach(AERO_L_PIN);
}

void loop() {
  IMU.read(); // Grab Gyro and Accel data points

  float ax = IMU.a.x * ACCEL_CONVERSION_FACTOR;
  float ay = IMU.a.y * ACCEL_CONVERSION_FACTOR;
  float az = IMU.a.z * ACCEL_CONVERSION_FACTOR;

  float gx = IMU.g.x * GRYO_CONVERSION_FACTOR;
  float gy = IMU.g.y * GRYO_CONVERSION_FACTOR;
  float gz = IMU.g.z * GRYO_CONVERSION_FACTOR;

  Serial.println("AccelX: " + (String)ax);

  //aeroR.write((int)floor(constrain((gy * 90) + 90, SERVO_DEAD_ZONE, 180 - SERVO_DEAD_ZONE)));
  //aeroL.write((int)floor(constrain((ay * -90) + 90, SERVO_DEAD_ZONE, 180 - SERVO_DEAD_ZONE)));
}
