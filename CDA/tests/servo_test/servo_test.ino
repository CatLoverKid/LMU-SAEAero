/* Requirements:
 * Servo connected to Digital Pin 6
 * Optional: Connect Capacitor across VCC and GND
 *    of Servo for smooth movement.
 *    Servo uses PWM, which is impacted by an unclean voltage source
 * Uses standard of 115200 Baud
 */
 
#include <Servo.h>
#define SERVO_PIN 6;

Servo myservo;
int pos = 0;

void setup() {
  myservo.attach(SERVO_PIN);
}

void loop() {
  for (pos = 0; pos <= 180; pos += 1) {
    myservo.write(pos);
    delay(5);
  }
  for (pos = 180; pos >= 0; pos -= 1) {
    myservo.write(pos);
    delay(5);
  }
}
