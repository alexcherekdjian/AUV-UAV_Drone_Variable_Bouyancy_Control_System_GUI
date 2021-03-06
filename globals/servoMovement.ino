void normalize_position(int current) {
  if (current < LINEAR100_MIN) {
    current = LINEAR100_MIN;

  } else if (current > LINEAR100_MAX) {
    current = LINEAR100_MAX;
  }
}

void modulate_z(float event_z, float current_z) {
  if (event_z > (current_z + 5.0)) {
    
    linear_current_L -= 10;
    linear_current_R += 10;
    
    normalize_position(linear_current_R);
    normalize_position(linear_current_L);
    
    //LINEAR100_R.attach(LINEAR100PIN2, LINEAR100_MIN, LINEAR100_MAX);
    //LINEAR100_L.attach(LINEAR100PIN1, LINEAR100_MIN, LINEAR100_MAX);

    LINEAR100_L.writeMicroseconds(linear_current_L); // fix
    LINEAR100_R.writeMicroseconds(linear_current_R); // fix

  } else if ( event_z < (current_z - 5.0)) {

    linear_current_L += 10;
    linear_current_R -= 10;
    
    normalize_position(linear_current_R);
    normalize_position(linear_current_L);
    
    //LINEAR100_R.attach(LINEAR100PIN2, LINEAR100_MIN, LINEAR100_MAX);
    //LINEAR100_L.attach(LINEAR100PIN1, LINEAR100_MIN, LINEAR100_MAX);

    LINEAR100_L.writeMicroseconds(linear_current_L); // fix
    LINEAR100_R.writeMicroseconds(linear_current_R);

  } else {

   LINEAR100_L.writeMicroseconds(linear_current_L); // fix
   LINEAR100_R.writeMicroseconds(linear_current_R); // fix


    //LINEAR100_R.detach();
    //LINEAR100_L.detach();
  }
}

void modulate_both(float event_pressure, float current_pressure) {

  if (event_pressure > (current_pressure + 50)) {
    linear_current_R -= 10;
    linear_current_L -= 10;

    normalize_position(linear_current_R);
    normalize_position(linear_current_L);

    //LINEAR100_R.attach(LINEAR100PIN2, LINEAR100_MIN, LINEAR100_MAX);
    //LINEAR100_L.attach(LINEAR100PIN1, LINEAR100_MIN, LINEAR100_MAX);

    LINEAR100_L.writeMicroseconds(linear_current_L); // fix
    LINEAR100_R.writeMicroseconds(linear_current_R); // fix

  } else if ( event_pressure < (current_pressure - 50)) {
    linear_current_R += 10;
    linear_current_L += 10;

    normalize_position(linear_current_R);
    normalize_position(linear_current_L);

    //LINEAR100_R.attach(LINEAR100PIN2, LINEAR100_MIN, LINEAR100_MAX);
    //LINEAR100_L.attach(LINEAR100PIN1, LINEAR100_MIN, LINEAR100_MAX);

    LINEAR100_L.writeMicroseconds(linear_current_L); // fix
    LINEAR100_R.writeMicroseconds(linear_current_R); // fix

  } else {

    LINEAR100_L.writeMicroseconds(linear_current_L); // fix
    LINEAR100_R.writeMicroseconds(linear_current_R); // fix

    //LINEAR100_R.detach();
    //LINEAR100_L.detach();

  }
}
