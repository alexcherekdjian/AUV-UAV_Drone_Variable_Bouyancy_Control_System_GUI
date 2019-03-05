String message;
boolean recvInProgress = false;
boolean newData = false;
float orientation_z_value = 0.0;
float pressure_value = 0.0;
String[] list;

void serialEvent() {
  // get message till line break (ASCII > 13)

   //char endMarker = '>';
   //println("inside serialEvent()");
  //if (port.available() > 0){

       // wait
       // 13 is ascii for newline
      message = port.readString(); // 'new line' 

      if(message != null){ 
        print("message: ");
        println(message);
        println("end of message");
       parseData();
      }
      delay(100);
 // }
}

void parseData() {      // split the data into its parts

//  char strtokIndx;
//  strtokIndx = strtok(message, ","); // this continues where the previous call left off
//  orientation_z_value = atoi(strtokIndx);     // convert this part to an integer
  list = split(message, ',');
  print("Orientation Sensor Reading: ");
  println(list[0]);
  
  print("Pressure Sensor Reading: ");
  println(list[1]);
}
