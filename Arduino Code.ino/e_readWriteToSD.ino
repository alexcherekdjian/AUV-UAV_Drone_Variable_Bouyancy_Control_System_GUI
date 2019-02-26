/*
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11 // Arduino to sd
 ** MISO - pin 12 // sd to arduino
 ** CLK - pin 13
 ** CS - pin 4 
*/

void write() {
  if (myFile) {
    Serial.print("Write to ");
    Serial.print(fname);
    myFile.println("[Data we want to write goes here]");
    // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    Serial.print("error opening");
    Serial.println(fname);
  }
}

void read() {
  myFile = SD.open(fname);
  if (myFile) {
    Serial.println(fname);

    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.print("error opening: ");
    Serial.println(fname);
  }
}
