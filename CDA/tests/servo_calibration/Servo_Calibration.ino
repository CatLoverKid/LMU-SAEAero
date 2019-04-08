#include <Servo.h>

#define LINE_BREAK "***********************************************"

//pinouts for each Servo
#define AERO_R_PIN 6
#define AERO_L_PIN 5 
#define SERVO_INIT_MAX 45
#define SERVO_INIT_MIN -45

//Creating Servo object
Servo aeroR;
Servo aeroL;


//Servo Position Values
int R_actual_pos = 90; //Represents the final Value being written to the servo
int R_offset_calibrate = 0; //Represents the relative offset needed to have the relative position be proper
int R_relative_pos = 0; //Represents where the flap is in relation to the wing

int L_actual_pos = 90; //Represents the final Value being written to the servo
int L_offset_calibrate = 0; //Represents the relative offset needed to have the relative position be proper
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

void move_absolute_servo(int R_desired_pos, int L_desired_pos) {
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
    if ((String)received_string == "DONE"){
      Serial.println(LINE_BREAK);
      Serial.println("Calibration for RIGHT servo complete");
      break;
    }else{
      R_offset_calibrate = received_string.toInt();
      move_absolute_servo(0, 0);
      Serial.println("New Relative Offset for RIGHT: " + (String)R_offset_calibrate);
    }
  }
  Serial.println("Final RIGHT Calibration: " + (String)R_offset_calibrate);

  Serial.println(LINE_BREAK);
  Serial.println("Calibrating LEFT Servo");
  move_absolute_servo(0, 0);
  Serial.println("Please enter a number in order to set the relative offset, type DONE to move on");
  while(true){
    received_string = read_input();
    if ((String)received_string == "DONE"){
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
  aeroR.attach(AERO_R_PIN);
  aeroL.attach(AERO_L_PIN);
  calibrate_servos();
  debug_dump();
}

void loop() {
//  while(R_relative_pos < 30){s
//    if (R_relative_pos == 0){
//      delay(1000);
//    }
//    move_absolute_servo(R_relative_pos + 3,0);
//    Serial.println(R_relative_pos);
//    delay(50);
//  }
//  while(R_relative_pos > -30){
//    if (R_relative_pos == 0){
//      delay(1000);
//    }
//    move_absolute_servo(R_relative_pos - 3,0);
//    Serial.println(R_relative_pos);
//    delay(50);
//  }
}
