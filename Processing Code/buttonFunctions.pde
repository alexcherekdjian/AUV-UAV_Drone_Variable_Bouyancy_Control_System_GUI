/* Button Functions */ 

void bar(int n){
  switch(n){
    
    case(0): 
      auto = false;
      manual = true;   
      break;
    
    case(1):
      auto = true;
      manual = false;
      break;
  }
}

void enter(){
  
  if(manual == true){
     println("'l' written to serial out");
     
     int left_value = ((int)cp5.getController("Left Servo").getValue() - 1050)/5;
     int right_value = ((int)cp5.getController("Right Servo").getValue() - 1050)/5; // convert back == right_value * 5 +1050
     
     String out = "<" + left_value + "," + right_value + ">";
     
     println("'l' written to serial out");
     println("Data out: " + out);
     port.write('l');
     port.write(out);
      
  }
}

// go down (fill both servos)
void depthUp(){
  
  if(manual == true){
    port.write('u');  
    println("'u' written to serial out");
  }
}

// go up (empty both servos)
void depthDown(){

  if(manual == true){
    port.write('d');  
    println("'d' written to serial out");
  }
}

void killSwitch(){
  if(manual == true || auto == true){
    port.write('k');
    println("'k' written to serial out");
  }
}
