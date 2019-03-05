void recvWithStartEndMarkers() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;

    while (Serial.available() > 0 && newData == false) {
        rc = Serial.read();

        if (recvInProgress == true) {
            if (rc != endMarker) {
                receivedChars[ndx] = rc;
                
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else {
                receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }

        else if (rc == startMarker) {
            recvInProgress = true;
        }
    }
}

void parseData() {      // split the data into its parts

  char * strtokIndx; // this is used by strtok() as an index


  strtokIndx = strtok(tempChars, ","); // this continues where the previous call left off
  left_input = atoi(strtokIndx);     // convert this part to an integer

  strtokIndx = strtok(NULL, ",");
  right_input = atoi(strtokIndx);     // convert this part to a integer float = atof

  left_input = (left_input * 5) + 1050; // rescaling integers
  right_input = (right_input * 5) + 1050;
}
