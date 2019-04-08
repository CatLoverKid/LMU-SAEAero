#include <Servo.h>
#include <LSM6.h>
#include <Wire.h>

#define LINE_BREAK "***********************************************"

// Default pins for Arduino's Wire Library
#define IMU_SCL_PIN "A4"
#define IMU_SDA_PIN "A5"

// Conversion Factors for IMU
#define ACCEL_CONVERSION_FACTOR 0.000061
#define GRYO_CONVERSION_FACTOR 0.001

//pinouts for each Servo
#define AERO_R_PIN 6
#define AERO_L_PIN 5 
#define SERVO_INIT_MAX 50
#define SERVO_INIT_MIN -90

#define SERVO_RIGHT_MAX 30
#define SERVO_RIGHT_MIN -90
#define SERVO_LEFT_MAX 60
#define SERVO_LEFT_MIN -60

//Creating various objects (Servo and IMU)
Servo aeroR;
Servo aeroL;
LSM6 IMU;

float ax, ay, az = 0;

//Servo Position Values
int R_actual_pos = 90; //Represents the final Value being written to the servo
int R_offset_calibrate = 18; //Represents the relative offset needed to have the relative position be proper
int R_relative_pos = 0; //Represents where the flap is in relation to the wing

int L_actual_pos = 90; //Represents the final Value being written to the servo
int L_offset_calibrate = 10; //Represents the relative offset needed to have the relative position be proper
int L_relative_pos = 0; //Represents where the flap is in relation to the wing

int clamp (int to_change, int minimum, int maximum) {
  return (to_change < minimum) ? (minimum) : ((to_change > maximum) ? (maximum) : (to_change));
}

String read_input () {
  byte incoming_byte = -1;
  String final_string = "";
  while(true){
    if(Serial.available() > 0){
      incoming_byte = Serial.read();
      if (incoming_byte == 10){
        break;
      }
      final_string += char(incoming_byte);
    }
  }
  return final_string;
}

void debug_dump(){
  Serial.println(LINE_BREAK);
  Serial.println(">>> VALUE DUMP <<<");
  Serial.println("Servo Info:");
  Serial.println("  Right Actual Position: " + (String)R_actual_pos);
  Serial.println("  Right Relative Offset: " + (String)R_offset_calibrate);
  Serial.println("  Right Relative Position: " + (String)R_relative_pos);
  Serial.println("  Left  Actual Position: " + (String)L_actual_pos);
  Serial.println("  Left  Relative Offset: " + (String)L_offset_calibrate);
  Serial.println("  Left  Relative Position: " + (String)L_relative_pos);
  Serial.println(LINE_BREAK);
}

void initialize_IMU(){
  Wire.begin(); // IMU uses Wire, which by default uses SDA and SCL on the Arduino (A4 and A5)
  if (!IMU.init()) {
    Serial.println("Failed to detect and initialize IMU!");
    Serial.println("Exiting");
    while (1);
  }
  IMU.enableDefault();
}

void collect_IMU_data(float & x, float & y, float & z){
  x,y,z = 0;
  float x_array[10];
  float y_array[10];
  float z_array[10];
  for(int i = 0; i < 10; i++){
    IMU.read();
    x_array[i] = IMU.a.x * ACCEL_CONVERSION_FACTOR;
    y_array[i] = IMU.a.y * ACCEL_CONVERSION_FACTOR;
    z_array[i] = IMU.a.z * ACCEL_CONVERSION_FACTOR;
  }
  for(int i = 0; i < 10; i++){
    x += x_array[i];
    y += y_array[i];
    z += z_array[i];
  }
  x /= 10;
  y /= 10;
  z /= 10;
}

void print_inclination(float pitch, float roll){
  if (pitch >= 0){
    Serial.print((String)(int)(pitch * 90) + " Degrees Down ,");
  }else{
    Serial.print((String)(int)(pitch * -90) + " Degrees Up, ");
  }
  if(roll >= 0){
    Serial.print((String)(int)(roll * 90) + " Degrees Left\n");
  }else{
    Serial.print((String)(int)(roll * -90) + " Degrees Right\n");
  }
}

void move_absolute_servo(int R_desired_pos, int L_desired_pos) {
  R_desired_pos *= -1;
  R_actual_pos = 90 + R_desired_pos + R_offset_calibrate;
  R_relative_pos = R_actual_pos - 90 - R_offset_calibrate;
  aeroR.write(R_actual_pos);
  
  L_actual_pos = 90 + L_desired_pos + L_offset_calibrate;
  L_relative_pos = L_actual_pos - 90 - L_offset_calibrate;
  aeroL.write(L_actual_pos);
}

void calibrate_servos(){
  String received_string = "";
  Serial.println(LINE_BREAK);
  Serial.println(">>> Beginning Servo Calibration <<<");
  Serial.println("Calibrating RIGHT Servo");
  move_absolute_servo(0, 0);
  Serial.println("Please enter a number in order to set the relative offset, type DONE to move on");
  while(true){
    received_string = read_input();
    if ((String)received_string == "done"){
      Serial.println(LINE_BREAK);
      Serial.println("Calibration for RIGHT servo complete");
      break;
    }else{
      R_offset_calibrate = received_string.toInt() * -1;
      move_absolute_servo(0, 0);
      Serial.println("New Relative Offset for RIGHT: -" + (String)R_offset_calibrate);
    }
    delay(300);
    Serial.println("Waiting...");
  }
  Serial.println("Final RIGHT Calibration: " + (String)R_offset_calibrate);

  Serial.println(LINE_BREAK);
  Serial.println("Calibrating LEFT Servo");
  move_absolute_servo(0, 0);
  Serial.println("Please enter a number in order to set the relative offset, type DONE to move on");
  while(true){
    received_string = read_input();
    if ((String)received_string == "done"){
      Serial.println(LINE_BREAK);
      Serial.println("Calibration for LEFT servo complete");
      break;
    }else{
      L_offset_calibrate = received_string.toInt();
      move_absolute_servo(0, 0);
      Serial.println("New Relative Offset for LEFT: " + (String)L_offset_calibrate);
    }
  }
  Serial.println("Final LEFT Calibration: " + (String)L_offset_calibrate);
  Serial.println(LINE_BREAK);
  move_absolute_servo(0, 0);
}

void setup() {
  Serial.begin(115200);
  Serial.println(LINE_BREAK);
  Serial.println("LMU SAE Aero IMU Filtering and Servo Control Test");
  Serial.println(LINE_BREAK);
  aeroR.attach(AERO_R_PIN);
  aeroL.attach(AERO_L_PIN);
  //initialize_IMU();
  calibrate_servos();
  debug_dump();
}

void loop() {
  calibrate_servos();
//  int vertical_deflect_required, horizontal_deflect_required;
//  collect_IMU_data(ax, ay, az);
//  vertical_deflect_required = ax * 25;
//  horizontal_deflect_required = ay * -25;
//  int final_R_degree = clamp(vertical_deflect_required + horizontal_deflect_required, SERVO_INIT_MIN, SERVO_INIT_MAX);
//  int final_L_degree = clamp(vertical_deflect_required - horizontal_deflect_required, SERVO_INIT_MIN, SERVO_INIT_MAX);
//  move_absolute_servo(final_R_degree, final_L_degree);
//  print_inclination(ax, ay);
//  delay(10);
}
