String message;
boolean recvInProgress = false;
boolean newData = false;
float orientation_z_value = 0.0;
float pressure_value = 0.0;

void serialEvent(Serial p) {
  // get message till line break (ASCII > 13)
  

   //char endMarker = '>';
  

    
  if (port.available() > 0){

       // wait
       message = port.readStringUntil(13); // 'new line'       
      if(message != null){ 
       
       //parseData();
    
     }
  }
}

//void parseData() {      // split the data into its parts

//  char strtokIndx;
//  strtokIndx = strtok(message, ","); // this continues where the previous call left off
//  orientation_z_value = atoi(strtokIndx);     // convert this part to an integer

  
//}
