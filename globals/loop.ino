void loop(void)
{

  /* Get a new sensor event */
  // get orientation data
  bno.getEvent(&event);


  sensor.read();

  Serial.print("Pressure: "); 
  Serial.print(sensor.pressure()); 
  Serial.println(" mbar");
  
  Serial.print("Temperature: "); 
  Serial.print(sensor.temperature()); 
  Serial.println(" deg C");
  
  Serial.print("Depth: "); 
  Serial.print(sensor.depth()); 
  Serial.println(" m");
  
  Serial.print("Altitude: "); 
  Serial.print(sensor.altitude()); 
  Serial.println(" m above mean sea level");

  delay(1000);

  // get pressure data
  //myFile.println(sensor.read());

  /* Optional: Display calibration status */
  //displayCalStatus();

  /* Optional: Display sensor status (debug only) */
  //displaySensorStatus();
  //serialEvent();
  // servo logic
  if (Serial.available()) {
    char val = Serial.read();
   // char val = 'p';

    if (val == 'l') {
      // manual overide set servos to certain values
      //Serial.println(val);
      Serial.print(event.orientation.z,4);
      Serial.print(", ");
      Serial.println(sensor.pressure());
      // recieve two bytes that denote left and right servo position
      recvWithStartEndMarkers();
      
      if (newData == true) {
        strcpy(tempChars, receivedChars);
            // this temporary copy is necessary to protect the original data
            //   because strtok() used in parseData() replaces the commas with \0
        parseData();

        newData = false;
      }
        // write to servos
        LINEAR100_R.writeMicroseconds(right_input); // MAX: syringe full
        LINEAR100_L.writeMicroseconds(left_input); // MAX: syringe full
 
       // update current
        linear_current_L = left_input;
        linear_current_R = right_input;

    } else if (val == 'd') {
      // go down (fill both servos completely)
      Serial.print(event.orientation.z,4);
      Serial.print(", ");
      Serial.println(sensor.pressure());
      update_z = true;
      update_pressure = true;

      LINEAR100_R.writeMicroseconds(LINEAR100_MAX); // MAX: syringe full
      LINEAR100_L.writeMicroseconds(LINEAR100_MAX); // MAX: syringe full

      linear_current_L = LINEAR100_MAX;
      linear_current_R = LINEAR100_MAX;

    } else if (val == 'u') {
      // go up (empty both servos completely)
      //Serial.println("Emptying both servos completely");
       Serial.print(event.orientation.z,4);
        Serial.print(", ");
        //Serial.write("HELLO");
        Serial.println(sensor.pressure());
      update_z = true;
      update_pressure = true;

      LINEAR100_R.writeMicroseconds(LINEAR100_MIN); // MIN: syringe empty
      LINEAR100_L.writeMicroseconds(LINEAR100_MIN); // MIN: syringe empty

      linear_current_L = LINEAR100_MIN;
      linear_current_R = LINEAR100_MIN;

      
    } else if (val == 'm') {

      Serial.print(event.orientation.z,4);
        Serial.print(", ");
        //Serial.write("HELLO");
        Serial.println(sensor.pressure());
      modulate_z(event.orientation.z, 5.5);
      // eventually need to quit out if user calls another command

    } else if (val == 'e' ) {
      // maintain current depth
      //update_z = true; // may be wrong logic
      //Serial.println("In maintain current depth");
      Serial.print(event.orientation.z,4);
        Serial.print(", ");
        //Serial.write("HELLO");
        Serial.println(sensor.pressure());

      modulate_both(sensor.pressure(), 1060);

    } else if(val == 'p'){
        // write the current z orientation to gui to print

        //figure out how to stream data onto the gui
         Serial.print(event.orientation.z,4);
        Serial.print(", ");
        //Serial.write("HELLO");
        Serial.println(sensor.pressure());
        
        // write the current pressure->depth reading to gui to print
        //Serial.print(sensor.pressure());
      
    } else if (val == 'k') {
      Serial.print(event.orientation.z,4);
        Serial.print(", ");
        //Serial.write("HELLO");
        Serial.println(sensor.pressure());
      // kill switch
      LINEAR100_L.writeMicroseconds(LINEAR100_MIN); // fix
      LINEAR100_R.writeMicroseconds(LINEAR100_MIN); // fix

    }
    delay(50);
  } else {
   //Serial.println("1 2 3");
    //will print on the processing side.
  }
  /* Wait the specified delay before requesting nex data */
  delay(BNO055_SAMPLERATE_DELAY_MS);
}
