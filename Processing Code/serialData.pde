String message;
boolean firstData = true;
float orientation_z_value = 0.0;
float pressure_value = 0.0;

void serialEvent(Serial p) {
  // get message till line break (ASCII > 13)
  

   //char endMarker = '>';

    
  if (port.available() > 0){
      
     message = port.readStringUntil(13); // 'new line'
     
     if(message != null){ 
       if(firstData){
          orientation_z_value = float(message);
          println("orientation: " + orientation_z_value);
         // firstData = false;
          
       }else{
          //pressure_value = float(message);
          //println("pressure: " + pressure_value);
          //firstData = true;
       }
     }
  }
 
}

void parseData() {      // split the data into its parts

  
}
