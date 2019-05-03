void loop() {
  imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
float orientation_trim = 167.00;
    /* Display the floating point data */
//    Serial.print("X: ");
//    Serial.print(euler.x());
//    Serial.print(" Y: ");
//    Serial.print(" - ");
//    Serial.print(euler.y());

//   Serial.print(" - ");
//    Serial.print(euler.z() - orientation_trim);
//    Serial.print(" - ");

  /* Display calibration status for each sensor. */


//   full left           mid                full right
//       13  to   0.5  to    -17
  
//  uint8_t system, gyro, accel, mag = 0;
//  bno.getCalibration(&system, &gyro, &accel, &mag);
//  Serial.print("CALIBRATION: Sys=");
//  Serial.print(system, DEC);
//  Serial.print(" Gyro=");
//  Serial.print(gyro, DEC);
//  Serial.print(" Accel=");
//  Serial.print(accel, DEC);
//  Serial.print(" Mag=");
//  Serial.println(mag, DEC);


  
  bno.getEvent(&event);
  //modulate_pitch(event.orientation.y , -15);
//    pwm.setPWM(0, 0, 240); // pin number , 0, final position (240 - 400) (-5) (235, 240)
//    pwm.setPWM(1, 0, 240);
//    pwm.setPWM(2, 0, 240);

///////////////////////////////////// PRESSURE STUFF /////////////////////////////////////
  float pressure_trim = 0.30; // 0.3

  sensor.read();

  float depth = sensor.depth();
//  Serial.print(depth*3.28084 - pressure_trim); 
//  Serial.print(" ft");
//  
// initialize input and setpoint
 Input_depth = depth*3.28084 - pressure_trim;
 Setpoint_depth = 1.5;

 Input_roll = event.orientation.z - orientation_trim;
 Setpoint_roll = -166.0;


//          pitch down

// y -4       -8.5      

 Input_pitch = event.orientation.y;
 Setpoint_pitch = -7.0;

if(use_pid_depth){
  // calculate pid stuff
   //Serial.println("DEPTH PID ACTIVE");
   depth_PID.Compute();
   int out = Output_depth; // casting to int
  
  // output PID Output to console
   Serial.print(" - ");
   Serial.println(out); 
   Serial.println("");
   
  // normalize output just for safety
   normalize_position(out);
   
  // move left and right based on pwm
   pwm.setPWM(0, 0, out); 
   pwm.setPWM(2, 0, out);
  // based on current position either call go up or go down for front servo
  
    if(Output_depth > linear_current_F){
      godown_PID(out, 1);
    }else{
      goup_PID(out, 1);
    }

   linear_current_L = out;
   linear_current_F = out;
   linear_current_R = out;
    
} else if(use_pid_roll_left){
  // calculate pid stuff
   roll_PID.Compute();
   int out = Output_roll; // casting to int
   
  // output PID Output to console
   Serial.print(" - ");
   Serial.println(out); 
   Serial.println("");
   
  // normalize output just for safety
   normalize_position(out);

  //int difference = linear_current_R-out; // get difference of current position to what will be writing to so we can command other side to do the opposite
   
   linear_current_L = out;
   //linear_current_R = out;
   
  // move left and right based on pwm
   pwm.setPWM(0, 0, linear_current_L); 
   //pwm.setPWM(2, 0, linear_current_R);
  // based on current position either call go up or go down for front servo
  
} else if(use_pid_pitch){
   pitch_PID.Compute();
   int out = Output_pitch; // casting to int
  
  // output PID Output to console
   Serial.print(" - ");
   Serial.println(out);
   Serial.println("");
   
  // normalize output just for safety
   normalize_position(out);
   
  // move left and right based on pwm
  // based on current position either call go up or go down for front servo
  
//    if(Output_pitch > linear_current_F){
//      godown_PID(out, 1);
//    }else{
//      goup_PID(out, 1);
//    }

   linear_current_F = out;

   pwm.setPWM(1, 0, linear_current_F);
}


  unsigned long ms;
  ms = millis();

  Serial.print("\tTime: ");
  Serial.print((ms/1000) - 9);

unsigned long ms_real = (ms/1000) - 9;
  int set_time = 0; 
  
if(use_thruster){
  if(((ms_real > set_time) && (ms_real) < set_time+10)){
    
      esc.writeMicroseconds(thrust);
      if(printstart){
        Serial.print("\tTHRUSTER Started");
        printstart = false;
      }
  }

  if((ms_real > set_time+10) && (ms_real < set_time+20)){
      esc.writeMicroseconds(1500);
        if(printstop){
          Serial.print("\tTHRUSTER Stopped");
          printstop = false;
      }
  }

    if(ms_real > set_time+20){

        if(printup){
          Serial.print("\tGOING UP");
          printup = false;
        }
      use_pid_depth = false;
      pwm.setPWM(0, 0, 240); // pin number , 0, final position (240 - 400) (-5) (235, 240)
      pwm.setPWM(1, 0, 240);
      pwm.setPWM(2, 0, 240);
      
  }
}

//  fuck = true;
//  wasteTime();

//  if(switch_pid){
//    switch_pid = false;
//  }else{
//    switch_pid = true;
//  }
  
  
  //Serial.println("DELAYING . . .");
  Serial.println("");
  delay(BNO055_SAMPLERATE_DELAY_MS);
  //delay(500);

}
