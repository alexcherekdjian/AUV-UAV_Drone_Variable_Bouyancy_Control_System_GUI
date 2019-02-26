void loop(void)
{

  /* Get a new sensor event */

  // get orientation data
  bno.getEvent(&event);

  // get pressure data
  sensor.read();

  /* Optional: Display calibration status */
  //displayCalStatus();

  /* Optional: Display sensor status (debug only) */
  //displaySensorStatus();

  // servo logic
  if (Serial.available()) {
    
    char val = Serial.read();

    if (val == 'l') {
      // manual overide set servos to certain values

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
      update_z = true;
      update_pressure = true;

      LINEAR100_R.writeMicroseconds(LINEAR100_MAX); // MAX: syringe full
      LINEAR100_L.writeMicroseconds(LINEAR100_MAX); // MAX: syringe full

      linear_current_L = LINEAR100_MAX;
      linear_current_R = LINEAR100_MAX;

    } else if (val == 'u') {
      // go up (empty both servos completely)
      update_z = true;
      update_pressure = true;

      LINEAR100_R.writeMicroseconds(LINEAR100_MIN); // MIN: syringe empty
      LINEAR100_L.writeMicroseconds(LINEAR100_MIN); // MIN: syringe empty

      linear_current_L = LINEAR100_MIN;
      linear_current_R = LINEAR100_MIN;

      
    } else if (val == 'm') {
     
      // maintain current roll
      //update_pressure = true;

      //      if(update_z){
      //        current_z = event.orientation.z; // update current z value to current maintain value
      //        update_z = false; // set bool to false
      //
      //      }

      while (val == 'm'){
        modulate_z(event.orientation.z, 5.5);

        if(Serial.available()){
          if(Serial.peek() != 'm'){
            break;
          }
        }
      }
      // eventually need to quit out if user calls another command

    } else if (val == 'e' ) {
      // maintain current depth
      //update_z = true; // may be wrong logic

      //      if(update_pressure){
      //        current_pressure = sensor.pressure(); // update current pressure value to current maintain value
      //        //current_depth = current_pressure * 0.01; // converting mbar -> meters
      //
      //        update_pressure = false; // set bool to false
      //
      //      }
     
     while (val == 'e'){

        modulate_both(sensor.pressure(), 1060);
        
        if(Serial.available()){
          if(Serial.peek() != 'e'){
            break;
          }
        }
      }
    } else if(val == 'p'){
        // write the current z orientation to gui to print

        String out = String(event.orientation.z, 4);
        out += ",";
        out += String(sensor.pressure());
        
         //Serial.println(event.orientation.z,4);

         Serial.println(out);
        // write the current pressure->depth reading to gui to print
         //Serial.print(sensor.pressure());
      
    } else if (val == 'k') {

      // kill switch
      LINEAR100_L.writeMicroseconds(LINEAR100_MIN); // fix
      LINEAR100_R.writeMicroseconds(LINEAR100_MIN); // fix

    }


    
    //    else {
    //      update_z = true;
    //      update_pressure = true;
    //
    //    }

  }
  /* Wait the specified delay before requesting nex data */
  delay(BNO055_SAMPLERATE_DELAY_MS);
}
