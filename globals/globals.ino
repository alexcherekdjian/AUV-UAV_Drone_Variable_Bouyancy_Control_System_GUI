#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <Servo.h>
#include "MS5837.h"

#define BNO055_SAMPLERATE_DELAY_MS (100) // Set the delay between fresh samples

// servo pin numbers
#define LINEAR100PIN1 9 // left servo
#define LINEAR100PIN2 10 // right servo

// servo max and min values
#define LINEAR100_MIN 1050 // Syringe Empty
#define LINEAR100_MAX 1700 // Syringe Full

// servo objects
Servo LINEAR100_L, LINEAR100_R;

// pressure sensor object
MS5837 sensor; 

// orientation sensor object
Adafruit_BNO055 bno = Adafruit_BNO055(55);

// update values
bool update_z = true; // denotes whether we need to update a new value of z or not
bool update_pressure = true; // denotes whether we need to update a new depth to maintain or not
float current_z;
float current_pressure; // mbar
float current_depth; // meters

// current servo positions
int linear_current_L = LINEAR100_MIN;
int linear_current_R = LINEAR100_MIN;

// recieving data globals
const byte numChars = 32;
char receivedChars[numChars];
char tempChars[numChars]; // temporary array for use when parsing
boolean newData = false;
int left_input = LINEAR100_MIN;
int right_input = LINEAR100_MIN;


sensors_event_t event;
