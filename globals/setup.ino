void setup(void)
{
  Serial.begin(9600);
  //Serial.println("Orientation Sensor Test"); Serial.println("");

//  // Set up for SD card
//  Serial.print("Initializing SD card...");
//
//  if (!SD.begin(CS)) {
//    Serial.println("Initialization failed");
//    while(1);
//  }
//  Serial.println("Initialization successful");
//
//  myFile = SD.open(fname, FILE_WRITE);
//  // End of set up

  // attaches/activates the linear actuator as a servo object
  LINEAR100_L.attach(LINEAR100PIN1, LINEAR100_MIN, LINEAR100_MAX);
  LINEAR100_R.attach(LINEAR100PIN2, LINEAR100_MIN, LINEAR100_MAX);

  //Analog pins do not need to be initialized
  LINEAR100_L.writeMicroseconds(LINEAR100_MIN);
  LINEAR100_R.writeMicroseconds(LINEAR100_MIN);

  /* Initialise the orientation sensor */
  if (!bno.begin()) {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    //Serial.write('o'); // let gui know orientation sensor not initialized
    //while (1);
  }

  delay(1000);

  /* Display some basic information on this sensor */
 // displaySensorDetails();

  /* Optional: Display current status */
  //displaySensorStatus();

  bno.setExtCrystalUse(true);

  // pressure sensor setup
  //Serial.println("Starting Pressure Sensor Setup . . .\n");

  Wire.begin();

  // Initialize pressure sensor
  // Returns true if initialization was successful
  // We can't continue with the rest of the program unless we can initialize the sensor
  if (!sensor.init()) {
    Serial.println("Init failed!");
    Serial.println("Are SDA/SCL connected correctly?");
    Serial.println("Blue Robotics Bar30: White=SDA, Green=SCL");
    Serial.println("\n\n\n");
    //Serial.write('p'); // let gui know pressure sensor not initialized
  }

  sensor.setModel(MS5837::MS5837_30BA);
  sensor.setFluidDensity(997); // kg/m^3 (997 freshwater, 1029 for seawater)
}
