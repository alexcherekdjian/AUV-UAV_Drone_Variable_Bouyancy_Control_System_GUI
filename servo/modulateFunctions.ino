void modulate_pitch(float event_orientation, float input_orientation) {
   int current_pl;
  if (event_orientation > (input_orientation + 0.5)) {

    linear_current_F += 5;

    normalize_position(linear_current_F);

    current_pl = map(linear_current_F, 0, 180, SERVOMIN, SERVOMAX); // degrees -> servomin max
    int delay_calc = map(linear_current_F, SERVOMIN, SERVOMAX, 0, 180);//  literally dont know

    pwm.setPWM(1, 0, linear_current_F);

    delay(-1*delay_calc*1); // * 2 is real slow
    
  } else if ( event_orientation < (input_orientation - 0.5)) {

    linear_current_F -= 5;

    normalize_position(linear_current_F);

    current_pl = map(linear_current_F, 0, 180, SERVOMIN, SERVOMAX); // degrees -> servomin max
    int delay_calc = map(linear_current_F, SERVOMIN, SERVOMAX, 0, 180);//  literally dont know

    pwm.setPWM(1, 0, linear_current_F);

    delay(-1*delay_calc*1); // * 2 is real slow
    
  } else {


  }
  
}

void modulate_all_down(float event_pressure, float input_pressure) {
   int current_pl;
  if (event_pressure > (input_pressure + 0.1)) {
    linear_current_R -= 5;
    linear_current_L -= 5;
    linear_current_F -= 5;

    normalize_position(linear_current_R);
    normalize_position(linear_current_L);
    normalize_position(linear_current_F);

    current_pl = map(linear_current_F, 0, 180, SERVOMIN, SERVOMAX); // degrees -> servomin max
    int delay_calc = map(linear_current_F, SERVOMIN, SERVOMAX, 0, 180);//  literally dont know

    pwm.setPWM(0, 0, current_pl); // pin number , 0, final position (265 - 400) (-5) (235, 240)
    pwm.setPWM(2, 0, current_pl);
    pwm.setPWM(1, 0, current_pl);

    delay(-1*delay_calc*1); // * 2 is real slow
  } else if ( event_pressure < (input_pressure - 0.1)) {
    linear_current_R += 5;
    linear_current_L += 5;
    linear_current_F += 5;

    normalize_position(linear_current_R);
    normalize_position(linear_current_L);
    normalize_position(linear_current_F);

    current_pl = map(linear_current_F, 0, 180, SERVOMIN, SERVOMAX); // degrees -> servomin max
    int delay_calc = map(linear_current_F, SERVOMIN, SERVOMAX, 0, 180);//  literally dont know

    pwm.setPWM(0, 0, current_pl); // pin number , 0, final position (265 - 400) (-5) (235, 240)
    pwm.setPWM(2, 0, current_pl);
    pwm.setPWM(1, 0, current_pl);

    delay(-1*delay_calc*1); // * 2 is real slow

    
  } else {

  }
  
}
