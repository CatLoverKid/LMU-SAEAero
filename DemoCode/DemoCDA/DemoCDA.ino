#include <Wire.h>
#include <LSM6.h>
#include <Servo.h>
#include <SoftwareSerial.h>
#include <Adafruit_GPS.h>

// Defining Mathematical Constants
#define ACCEL_CONVERSION_FACTOR 0.000061
#define GRYO_CONVERSION_FACTOR 0.001
#define SERVO_DEAD_ZONE 10

// Defining Pinouts
#define IMU_SDA_PIN "A5" // Changing SDA/SCL will require rewrite of code to support custom Wire Instance
#define IMU_SCL_PIN "A4" // See note for IMU_SDA_PIN, definition only here for hardware reference
#define GPS_RX_PIN 10
#define GPS_TX_PIN 11
#define AERO_R_PIN 5
#define AERO_L_PIN 6
#define XBEE_TX_PIN 8
#define XBEE_RX_PIN 9

// etc helpers constants
#define LINE_BREAK "***********************************************"
#define DEBUG_MODE false

Servo aeroR;
Servo aeroL;
LSM6 IMU;
SoftwareSerial GPSSerial (GPS_RX_PIN, GPS_TX_PIN); // Use Custom Serial Interface through param Pins
Adafruit_GPS GPS(&GPSSerial);
SoftwareSerial xbee(XBEE_TX_PIN, XBEE_RX_PIN);

// Necesary constant for determining if extra content is displayed
// from Adafruit Feather GPS, used for Debug purposes
#define GPSECHO false

//Internal Variables
int aeroRPos = 90;
int aeroLPos = 90;
uint32_t timer = millis();

void setup()
{
  // Initialize main Serial interface, for Debugging
  Serial.begin(115200);
  if (DEBUG_MODE) {
    Serial.println(LINE_BREAK);
    Serial.println("LMU SAE Aero Basic Demonstration and Test");
    Serial.println(LINE_BREAK);
  }

  // Initialize Internal Measurment Unit
  Wire.begin(); // IMU uses Wire, which by default uses SDA and SCL on the Arduino (A4 and A5)
  if (!IMU.init() && DEBUG_MODE) {
    Serial.println("Failed to detect and initialize IMU!");
    while (1);
  }
  IMU.enableDefault();

  // Initialize Servo motors
  aeroR.attach(AERO_R_PIN);
  aeroL.attach(AERO_L_PIN);

  // Initialize GPS Module
  GPS.begin(9600);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA); // Define Output Format
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ); // 1 Hz update rate
  GPS.sendCommand(PGCMD_ANTENNA); // Define Antenna Type
  delay(1000); // Provide ample time for GPS antenna to "warm up"
  GPSSerial.println(PMTK_Q_RELEASE); // Begin GPS

  //Begin XBee interface
  xbee.begin(9600);
}

void loop()
{
  // Handle Gyro/Accel, also move Servos
  IMU.read(); // Grab Gyro and Accel data points

  float ax = IMU.a.x * ACCEL_CONVERSION_FACTOR;
  float ay = IMU.a.y * ACCEL_CONVERSION_FACTOR;
  float az = IMU.a.z * ACCEL_CONVERSION_FACTOR;

  float gx = IMU.g.x * GRYO_CONVERSION_FACTOR;
  float gy = IMU.g.y * GRYO_CONVERSION_FACTOR;
  float gz = IMU.g.z * GRYO_CONVERSION_FACTOR;

  aeroR.write((int)floor(constrain((ay * 90) + 90, SERVO_DEAD_ZONE, 180 - SERVO_DEAD_ZONE)));
  aeroL.write((int)floor(constrain((ay * -90) + 90, SERVO_DEAD_ZONE, 180 - SERVO_DEAD_ZONE)));
  // Handle GPS
  char gps_output = GPS.read();
  if (GPSECHO)
  if (gps_output && DEBUG_MODE) Serial.print(gps_output);
  if (GPS.newNMEAreceived()) {
    Serial.println(GPS.lastNMEA());
    if (!GPS.parse(GPS.lastNMEA()))
    return;
  }
  if (timer > millis()) timer = millis();

  if (millis() - timer > 2000) {
    timer = millis(); // reset the timer
    Serial.print("\nTime: ");
    Serial.print(GPS.hour, DEC); Serial.print(':');
    Serial.print(GPS.minute, DEC); Serial.print(':');
    Serial.print(GPS.seconds, DEC); Serial.print('.');
    Serial.println(GPS.milliseconds);
    Serial.print("Date: ");
    Serial.print(GPS.day, DEC); Serial.print('/');
    Serial.print(GPS.month, DEC); Serial.print("/20");
    Serial.println(GPS.year, DEC);
    Serial.print("Fix: "); Serial.print((int)GPS.fix);
    Serial.print(" quality: "); Serial.println((int)GPS.fixquality);
    Serial.println("A: " + (String)ax + ", " + (String)ay + ", " + (String)az + " G: " + (String)gx + ", " + (String)gy + ", " + (String)gz);
    if (GPS.fix) {
      Serial.print("Location: ");
      Serial.print(GPS.latitude, 4); Serial.print(GPS.lat);
      Serial.print(", ");
      Serial.print(GPS.longitude, 4); Serial.println(GPS.lon);
      Serial.print("Speed (knots): "); Serial.println(GPS.speed);
      Serial.print("Angle: "); Serial.println(GPS.angle);
      Serial.print("Altitude: "); Serial.println(GPS.altitude);
      Serial.print("Satellites: "); Serial.println((int)GPS.satellites);
    }
  }

  // Send Telemetry Data over XBee
  xbee.write((ay * 90) + 90);
  xbee.write(GPS.latitude);
  xbee.write(GPS.longitude);
  xbee.write(GPS.speed);
  delay(30);
}
