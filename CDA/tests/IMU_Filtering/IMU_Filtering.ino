#include <Adafruit_LSM9DS1.h>
#include <Wire.h>

#define ACCEL_CONVERSION_FACTOR 0.000061
#define GYRO_CONVERSION_FACTOR 0.001

#define LINE_BREAK "***********************************************"

#define IMU_SCL_PIN "A4"
#define IMU_SDA_PIN "A5"

//nums
float gyro_x = 0;
float gyro_y = 0;
float gyro_z = 0;
float gyro_calibrate_x = 0;
float gyro_calibrate_y = 0;
float gyro_calibrate_z = 0;
float tmp_g_x = 0;
float tmp_g_y = 0;
float tmp_g_z = 0;
int count = 0;

sensors_event_t accel, mag, gyro, temp;


Adafruit_LSM9DS1 lsm = Adafruit_LSM9DS1();

void initialize_IMU(){
  Wire.begin(); // IMU uses Wire, which by default uses SDA and SCL on the Arduino (A4 and A5)
  while (!lsm.begin()) {
    Serial.println("Failed to detect and initialize IMU!");
    delay(5000);
  }
  lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_8G);
  lsm.setupMag(lsm.LSM9DS1_MAGGAIN_4GAUSS);
  lsm.setupGyro(lsm.LSM9DS1_GYROSCALE_245DPS);
}

void calibrate_gyro(float *x, float *y, float *z) {
  float tmpx = 0;
  float tmpy = 0;
  float tmpz = 0;
  float number_of_runs = 50;
  for (int i = 0; i < number_of_runs; i++){
    lsm.getEvent(&accel, &mag, &gyro, &temp);
    tmpx += gyro.gyro.x;
    tmpy += gyro.gyro.y;
    tmpz += gyro.gyro.z;
    Serial.println((String)millis()+","+(String)count+","+(String)gyro.gyro.x+","+(String)gyro.gyro.y+","+(String)gyro.gyro.z+",,,,,,,,,,Calibrating Gyro");
  }
  *x = tmpx / number_of_runs;
  *y = tmpy / number_of_runs;
  *z = tmpz / number_of_runs;
}

void collect_IMU_data(float *gx, float *gy, float *gz){
  int number_of_runs = 10;
  float vals[number_of_runs * 3];
  tmp_g_x = 0;
  tmp_g_y = 0;
  tmp_g_z = 0;
  
  for(int i = 0; i < number_of_runs; i++){
    lsm.getEvent(&accel, &mag, &gyro, &temp);
    vals[i + (0 * number_of_runs)] = gyro.gyro.x;
    vals[i + (1 * number_of_runs)] = gyro.gyro.y;
    vals[i + (2 * number_of_runs)] = gyro.gyro.z;
//    Serial.print((String)millis()+","+(String)count + ",");
//    Serial.print((String)IMU.g.x+","+(String)IMU.g.y+","+(String)IMU.g.z+",");
//    Serial.print((String)(IMU.g.x - gyro_calibrate_x)+","+(String)(IMU.g.y - gyro_calibrate_y)+","+(String)(IMU.g.z - gyro_calibrate_z)+",");
//    Serial.print((String)gyro_x+","+(String)gyro_y+","+(String)gyro_z+",");
//    Serial.println((String)gyro_calibrate_x+","+(String)gyro_calibrate_y+","+(String)gyro_calibrate_z+",");
    delay(5);
  }
  for(int i = 0; i < number_of_runs; i++){
    tmp_g_x += vals[i + (0 * number_of_runs)];
    tmp_g_y += vals[i + (1 * number_of_runs)];
    tmp_g_z += vals[i + (2 * number_of_runs)];
  }
  tmp_g_x = (tmp_g_x / number_of_runs) - gyro_calibrate_x;
  tmp_g_y = (tmp_g_y / number_of_runs) - gyro_calibrate_y;
  tmp_g_z = (tmp_g_z / number_of_runs) - gyro_calibrate_z;
  Serial.println((String)gyro.gyro.x + ", " + (String)gyro.gyro.y + ", " + (String)gyro.gyro.z + ", " + (String)*gx + ", " + (String)*gy + ", " + (String)*gz);
  *gx += tmp_g_x;
  *gy += tmp_g_y;
  *gz += tmp_g_z;
}

void setup() {
  delay(2000);
  Serial.begin(9200);
  Serial.println("time,run_cnt,dps_x,dps_y,dps_z,cal_adjust_x,cal_adjust_y,cal_adjust_z,deg_x,deg_y,deg_z,cal_x,cal_y,cal_z,notes");
  initialize_IMU();
  calibrate_gyro(&gyro_calibrate_x, &gyro_calibrate_y, &gyro_calibrate_z);
  Serial.println("FINAL CALIBRATION VALUES: " + (String)gyro_calibrate_x + ", " + (String)gyro_calibrate_y + ", " + (String)gyro_calibrate_z);
  delay(1000);
}

void loop() {
  count ++;
  collect_IMU_data(&gyro_x, &gyro_y, &gyro_z);
  delay(10);
}

