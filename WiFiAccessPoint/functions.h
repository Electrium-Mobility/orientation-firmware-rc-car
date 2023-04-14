// **************************** PIN AND VARIABLE DEFINITIONS **************************** //
// --------------------------- TODO ---------------------------
// Define which pins you want to use for the motor, you need at least 3 with motor driver
#define MOTOR_IN1 
#define MOTOR_IN2 
#define EN_PIN 
// --------------------------- TODO ---------------------------
// Define which pins you want to use for the Servo, you need 1 
#define SERVO_PIN 
// --------------------------- TODO ---------------------------
// Define what your SSID and Password is for your personal server! (Team name preferred :))
const char *ssid = "";
const char *password = "";

// **************************** FUNCTION FOR FORWARD AND BACKWARD MOTIONS **************************** //
void run_motor(int y){
  if (y < 0){  // To run RC Car Forward
    y = map(y, -200, 0, -255, -102);
    analogWrite(EN_PIN, abs(y));
  //  --------------------------- TODO ---------------------------
  // Digital write to MOTOR_IN1 and MOTOR_IN2 pins to go forwards
     
  } else if (y > 0){ // To run RC Car backwards
    y = map(y, 0, 200, 102, 255);
    analogWrite(EN_PIN, abs(y));
  //  --------------------------- TODO ---------------------------
  // Digital write to MOTOR_IN1 and MOTOR_IN2 pins to go backwards
     
  } else if (y == 0){
    
  }
  
}

// **************************** FUNCTION FOR TURNING MOTIONS **************************** //
void steer(int x){
//  --------------------------- TODO ---------------------------
// Turn x which is a number between -200 to 200 into a nubmer between 0 to 180
  x = map(x, -200, 200, 0, 180);
//  --------------------------- TODO ---------------------------
// Write to the servo motor the degrees it should be
  steering_servo.write(x);
}