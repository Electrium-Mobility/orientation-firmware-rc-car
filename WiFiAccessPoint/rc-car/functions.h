// **************************** THE BIGGER PICTURE AND WHAT WE NEED TO DO **************************** //

// We need to finish writing two important functions:
// run_motor, which is responsible for forwards and backwards motions


// **************************** PIN AND VARIABLE DEFINITIONS **************************** //
// --------------------------- TODO ---------------------------
// We need to define which pins of the ESP8266 we want our motor driver's input pins to be connected to
// Refer to diagram 1 and 2 in the documentation!
// In the electrical section, we connected pins D1 on the ESP8266 with the IN1 pin on the motor driver, D2 with IN2, and D5 with EEP
// This means that the pin we want IN1 to be defined by is the GPIO number beside D1, and the pin we want IN2 to be defined by is the GPIO number beside D2
// The first definition has been made for you as an example! Now complete MOTOR_IN2 and EN_PIN
// CHECK IF WE CAN DIRECTLY WRITE D1 AND D2
#define MOTOR_IN1 5
#define MOTOR_IN2 
#define EN_PIN 

// --------------------------- TODO ---------------------------
// Similarly, we connected D8 on the ESP8266 with the PWM pin on the servo motor. This means that the pin we want PWM to be defined by is the GPIO number beside D8
#define SERVO_PIN 

// --------------------------- TODO ---------------------------
// Name your wifi network and password for your personal server (team name preferred!)
// Note: make sure the password is at least 8 characters long
const char *ssid = "";
const char *password = "";


// **************************** FUNCTION FOR FORWARD AND BACKWARD MOTIONS **************************** //
void run_motor(int y){
  // forward motion
  if (y < 0){ 
    y = map(y, -200, 0, -255, -102);
    analogWrite(EN_PIN, abs(y));

    //  --------------------------- TODO ---------------------------
    // Now, we want to give the MOTOR_IN1 and MOTOR_IN2 pins the signals they need in order to go forwards!
    // Refer to table 1 in the documentation for the combination of signals to give both, in order for them to achieve a forward motion
    // The syntax for this is digitalWrite(pin, value)
    // Where pin is the pin number or variable name of the pin we want to send the signals to
    // And value is either HIGH or LOW
  } 
  // backward motion
  else if (y > 0){ 
    y = map(y, 0, 200, 102, 255);
    analogWrite(EN_PIN, abs(y));

    //  --------------------------- TODO ---------------------------
    // Do the same as above, but for reverse motion!
      
  } 
  // stationary
  else if (y == 0){
    //  --------------------------- TODO ---------------------------
    // Do the same as above, but if we want our car to be stationary!
  }
  
}

// **************************** FUNCTION FOR TURNING MOTIONS **************************** //
void steer(int x){
  //  --------------------------- TODO ---------------------------
  // This function receives a value x, a number between -200 and 200, which represents the x coordinate we received from our joystick
  // We want to write code that will turn x into a number between 0 to 180, which represents the number of degrees we want our car to turn
  // The syntax to do this is x = map(x, lower range 1, upper range 1, lower range 2, upper range 2)
  // Where lower range 1 and upper range 1 are the bounds of the original range we want to switch from
  // And lower range 2 and upper range 2 are the bounds of the new range we want to switch to

  // replace the zeroes with the correct values
  x = map(x, 0, 0, 0);

  // Write the new value for number of degrees we calculated to the servo motor 
  steering_servo.write(x);
}