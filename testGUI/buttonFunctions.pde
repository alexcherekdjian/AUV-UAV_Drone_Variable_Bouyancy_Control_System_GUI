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
     
     int left_value = ((int)cp5.getController("Left Servo").getValue() - 1050)/5;
     int right_value = ((int)cp5.getController("Right Servo").getValue() - 1050)/5; // convert back == right_value * 5 +1050
     
     String out = "<" + left_value + "," + right_value + ">";
     
     println("Command sent to servo");
     println("Position: " + out);
     port.write('l');
     port.write(out);
      
  }
}

// go down (fill both servos)
void depthUp(){
  
  if(manual == true){
    port.write('u');  
    println("Ascend");
  }
}

// go up (empty both servos)
void depthDown(){

  if(manual == true){
    port.write('d');  
    println("Descend");
  }
}

void killSwitch(){
  //if(manual == true || auto == true){
    char k = 'k';
    port.write(k);
   // print(k);
    println("Reset");
 // }
}

void pressure() {
  port.write('p');
  println("Pressure reading test");
 
}
