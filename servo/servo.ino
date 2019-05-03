#include <math.h>
#include <Servo.h>
#include <Wire.h>
#include "MS5837.h"

#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <Adafruit_PWMServoDriver.h>
#include <PID_v1.h>


#define SERVOMIN  240 // small safe max = 360 large safe max = 380
#define SERVOMAX  360  

#define BNO055_SAMPLERATE_DELAY_MS (100)
#define thrust_pin 9

bool printstart = true;
bool printstop = true;
bool printup = true;

Servo esc;

// 274
double Setpoint_depth; // end dest
double Input_depth; // event data
double Output_depth; // linear_current_L ex. servo current position

double Setpoint_roll; // end dest
double Input_roll; // event data
double Output_roll; // linear_current_L ex. servo current position

double Setpoint_pitch; // end dest
double Input_pitch; // event data
double Output_pitch; // linear_current_L ex. servo current position


double Kp = 125.0; // 2
double Ki = 7.5; // 2
double Kd = 0.0;

// 0 = left, 1 = front, 2 = right 
bool use_pid_depth = false;
bool use_pid_roll_left = false;
bool use_pid_pitch = false;

bool use_thruster = true;

bool hard_reset = true;

//The esc takes between 1100 and 1900. 1500 is neutral
int thrust = 1900; // pwm thrust value 

PID depth_PID(&Input_depth, &Output_depth, &Setpoint_depth, Kp, Ki, Kd, DIRECT); // kp,ki,kd
PID roll_PID(&Input_roll, &Output_roll, &Setpoint_roll, Kp, Ki, Kd, DIRECT); // kp,ki,kd
PID pitch_PID(&Input_pitch, &Output_pitch, &Setpoint_pitch, Kp, Ki, Kd, REVERSE); // kp,ki,kd

MS5837 sensor;


// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();



Adafruit_BNO055 bno = Adafruit_BNO055();

bool fuck = true;


sensors_event_t event;

// all servos current position
int linear_current_L = SERVOMIN;
int linear_current_R = SERVOMIN;
int linear_current_F = SERVOMIN;

// for goup and godown functioncs without PID
int current_degrees = 360;

void setup() {
   Serial.begin(9600);
  Serial.println("Orientation Sensor Raw Data Test"); Serial.println("");

  /* Initialise the sensor */
  if(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }

  delay(1000);

  /* Display the current temperature */
  int8_t temp = bno.getTemp();
  Serial.print("Current Temperature: ");
  Serial.print(temp);
  Serial.println(" C");
  Serial.println("");

  bno.setExtCrystalUse(true);

  Serial.println("Calibration status values: 0=uncalibrated, 3=fully calibrated");
 

  Wire.begin();

  // Initialize pressure sensor
  // Returns true if initialization was successful
  // We can't continue with the rest of the program unless we can initialize the sensor
  while (!sensor.init()) {
    Serial.println("Init failed!");
    Serial.println("Are SDA/SCL connected correctly?");
    Serial.println("Blue Robotics Bar30: White=SDA, Green=SCL");
    Serial.println("\n\n\n");
    delay(5000);
  }
  
  sensor.setModel(MS5837::MS5837_30BA);
  sensor.setFluidDensity(997); // kg/m^3 (freshwater, 1029 for seawater)

  pwm.begin();  
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

  // 0 = left, 1 = front, 2 = right 

 
  //pwm.setPWM(0, 0, 240); // pin number , 0, final position (240 - 400) (-5) (235, 240)
  //pwm.setPWM(2, 0, 240);
  //godown_PID(360, 1);
 
  
  //pwm.setPWM(0, 0, 235); // pin number , 0, final position (240 - 400) (-5) (235, 240)
  //pwm.setPWM(2, 0, 240);
  //goup_PID(240, 1);

  if(hard_reset){
    pwm.setPWM(0, 0, 240); // pin number , 0, final position (240 - 400) (-5) (235, 240)
    pwm.setPWM(1, 0, 240); // -3 not pitched, pitched up -10
    pwm.setPWM(2, 0, 240);
    
  }

  Serial.println("Waiting delay . . .");
  delay(500);
  
  Serial.println("Setting Mode . . .");
  depth_PID.SetMode(AUTOMATIC);
  roll_PID.SetMode(AUTOMATIC);
  pitch_PID.SetMode(AUTOMATIC);
  Serial.println("Setting Min and Max . . .");
  Serial.print("Servomin: ");
  Serial.println(SERVOMIN);
  Serial.print("Servomax: ");
  Serial.println(SERVOMAX);
  
  depth_PID.SetOutputLimits(SERVOMIN, SERVOMAX);
  roll_PID.SetOutputLimits(SERVOMIN, SERVOMAX);
  pitch_PID.SetOutputLimits(SERVOMIN, SERVOMAX);

  Serial.println("Attaching Thruster . . .");
  esc.attach(thrust_pin);
  esc.writeMicroseconds(1500);
  Serial.println("Thruster 7000 delay . . .");
  delay(7000);
  Serial.println("Thruster Complete");

  Serial.println("");

  Serial.println("Loop Entered");
  Serial.println(""); 
  Serial.println("");
}

void wasteTime(){

  while(fuck){
    
  }  
}

void godown_PID(int dest_degrees, int delay_mult){

      while(dest_degrees != linear_current_F){
            linear_current_F++;
            
            normalize_position(linear_current_F);
            pwm.setPWM(1, 0, linear_current_F);
            //pwm.setPWM(1, 0, current_pl);

            delay(70*delay_mult); // * 2 is real slow
      }
    fuck = false;

}

void goup_PID(int dest_degrees, int delay_mult){

      while(dest_degrees != linear_current_F){
            linear_current_F--;
            
            normalize_position(linear_current_F);
            pwm.setPWM(1, 0, linear_current_F);

            delay(70*delay_mult); // * 2 is real slow
      }
    fuck = false;

}

void godown(int dest_degrees, int delay_mult){

      while(dest_degrees != current_degrees){
            current_degrees++;
            int current_pl = map(current_degrees, 0, 180, SERVOMIN, SERVOMAX); // degrees -> servomin max
            int delay_calc = map(current_degrees, SERVOMIN, SERVOMAX, 0, 180);//  literally dont know

            pwm.setPWM(1, 0, current_pl);
            //pwm.setPWM(1, 0, current_pl);

            delay(-1*delay_calc*delay_mult); // * 2 is real slow
      }
    delay(1500);
    fuck = false;

}

void goup(int dest_degrees, int delay_mult){
      while(dest_degrees != current_degrees){
            current_degrees--;
            int current_pl = map(current_degrees, 0, 180, SERVOMIN, SERVOMAX); // degrees -> servomin max
            int delay_calc = map(current_degrees, SERVOMIN, SERVOMAX, 0, 180);//  literally dont know

            pwm.setPWM(1, 0, current_pl);
            //pwm.setPWM(1, 0, current_pl);
            
          
            delay(-1*delay_calc*delay_mult); // * 2 is real slow
      }
    //delay(1500);
    fuck = false;
}



void normalize_position(int &current) {
  if (current < SERVOMIN) {
    current = SERVOMIN;

  } else if (current > SERVOMAX) {
    current = SERVOMAX;
  }
}


void normalize_position_double(double &current) {
  if (current < SERVOMIN) {
    current = SERVOMIN;

  } else if (current > SERVOMAX) {
    current = SERVOMAX;
  }
}
