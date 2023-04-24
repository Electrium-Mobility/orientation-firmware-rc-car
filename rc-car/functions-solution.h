// **************************** PIN AND VARIABLE DEFINITIONS **************************** //
// --------------------------- TODO ---------------------------
#define MOTOR_IN1 5
#define MOTOR_IN2 4
#define EN_PIN 14

// --------------------------- TODO ---------------------------
// Similarly, we connected D8 on the ESP8266 with the PWM pin on the servo motor. This means that the pin we want PWM to be defined by is the GPIO number beside D8
#define SERVO_PIN 2

// --------------------------- TODO ---------------------------
// Rename the wifi network and password for your personal server (team name preferred!)
// Note: make sure the password is at least 8 characters long
const char *ssid = "Orientation-RC-Car";
const char *password = "temp-password";


// **************************** FUNCTION FOR FORWARD AND BACKWARD MOTIONS **************************** //
void run_motor(int y){
  
  // FORWARD MOTION
  if (y < 0){ 
    y = pow(abs(y) / 200, 0.5) * 200; // make the acceleration curve exponential instead of linear, so that there's more forward/reverse motion while turning
    y = map(y, 0, 200, 102, 255);
    analogWrite(EN_PIN, y);

    // --------------------------- TODO ---------------------------
    digitalWrite(MOTOR_IN1, HIGH);
    digitalWrite(MOTOR_IN2, LOW);  

  } 

  // REVERSE MOTION
  else if (y > 0){ 
    y = pow(abs(y) / 200, 0.5) * 200; // make the acceleration curve exponential instead of linear, so that there's more forward/reverse motion while turning
    y = map(y, 0, 200, 102, 255);
    analogWrite(EN_PIN, y);

    // --------------------------- TODO ---------------------------
    digitalWrite(MOTOR_IN1, LOW);
    digitalWrite(MOTOR_IN2, HIGH); 
  } 
  
  // STATIONARY
  else if (y == 0){
    // --------------------------- TODO ---------------------------
    digitalWrite(MOTOR_IN2, LOW);
    digitalWrite(MOTOR_IN1, LOW); 
  }
}

// **************************** FUNCTION FOR TURNING MOTIONS **************************** //
void steer(int x){
  // --------------------------- TODO ---------------------------
  x = map(x, -200, 200, 0, 180);

  // Write the new value for number of degrees we calculated to the servo motor 
  steering_servo.write(x);
}