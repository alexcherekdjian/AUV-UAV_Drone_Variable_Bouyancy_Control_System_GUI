void loop() {
  imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);

    /* Display the floating point data */
  //  Serial.print("X: ");
  //  Serial.print(euler.x());
  //  Serial.print(" Y: ");
  //  Serial.print(euler.y());
  //  Serial.print(" Z: ");
  //  Serial.print(euler.z());
  //  Serial.print("\t\t");

  /* Display calibration status for each sensor. */

  /*
  uint8_t system, gyro, accel, mag = 0;
  bno.getCalibration(&system, &gyro, &accel, &mag);
  Serial.print("CALIBRATION: Sys=");
  Serial.print(system, DEC);
  Serial.print(" Gyro=");
  Serial.print(gyro, DEC);
  Serial.print(" Accel=");
  Serial.print(accel, DEC);
  Serial.print(" Mag=");
  Serial.println(mag, DEC);

  delay(BNO055_SAMPLERATE_DELAY_MS);

  //float orientation_trim = 0;
  //bno.getEvent(&event);
  //modulate_pitch(event.orientation.y , -15);
*/

///////////////////////////////////// PRESSURE STUFF /////////////////////////////////////
  float pressure_trim = 0.1; 

  sensor.read();

  float depth = sensor.depth();
  Serial.print("Depth: "); 
  Serial.print(depth*3.28084 - pressure_trim); 
  Serial.println(" ft     ");

  Serial.println("");

  //modulate_all_down(depth*3.28084 - pressure_trim, 1.0);
//  fuck = true;
//  wasteTime();

  
  //delay(1000);


}
