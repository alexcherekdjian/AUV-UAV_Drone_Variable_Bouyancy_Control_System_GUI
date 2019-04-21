/*************************************************** 
  This is an example for our Adafruit 16-channel PWM & Servo driver
  Servo test - this will drive 8 servos, one after the other on the
  first 8 pins of the PCA9685

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/815
  
  These drivers use I2C to communicate, 2 pins are required to  
  interface.

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <Wire.h>
#include "MS5837.h"

#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <PID_v1.h>
//double Setpoint; // end dest
double Input; // event data
double Output; // linear_current_L ex. servo current position
double Kp;
double Ki;
double Kd; 

//PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT); // kp,ki,kd

MS5837 sensor;
#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN  250 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  380 // this is the 'maximum' pulse length count (out of 4096)

#define BNO055_SAMPLERATE_DELAY_MS (100)

Adafruit_BNO055 bno = Adafruit_BNO055();

bool fuck = true;

sensors_event_t event;

// all servos current position
int linear_current_L = SERVOMIN;
int linear_current_R = SERVOMIN;
int linear_current_F = SERVOMIN;

// for goup and godown functioncs
int current_degrees = 0;

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
  
  Serial.println("8 channel Servo test!");


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

 
  pwm.setPWM(0, 0, 240); // pin number , 0, final position (240 - 400) (-5) (235, 240)
  pwm.setPWM(1, 0, 240);
  pwm.setPWM(2, 0, 240);
  //godown(180, 0);

  
  //pwm.setPWM(0, 0, 235); // pin number , 0, final position (240 - 400) (-5) (235, 240)
  //pwm.setPWM(2, 0, 240);
  //goup(10, 0);



  //myPID.SetMode(AUTOMATIC);
  //myPID.SetOutputLimits(SERVOMIN, SERVOMAX);

  
}

void wasteTime(){

  while(fuck){
    
  }  
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
