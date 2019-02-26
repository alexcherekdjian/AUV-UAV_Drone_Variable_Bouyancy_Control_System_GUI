import controlP5.*; // gui object
import processing.serial.*;

Serial port;

ControlP5 cp5; 
PFont font1;
PFont font2;

boolean maintainRoll = false;
boolean commandSentRoll = false;
boolean maintainDepth = false;
boolean commandSentDepth = false;

boolean auto = false;
boolean manual = false;




int [] serialInArray; // buffer for reading values

void setup(){ // same as arduino
  
  size (500, 600); // window size (width, height)
  cp5 = new ControlP5(this); // object creation
  
  // print(PFont.list()); // list all the fonts
  
  printArray(Serial.list()); // prints all available serial ports
  port = new Serial(this, Serial.list()[3], 9600);
  
  // fonts
  font1 = createFont("Waseem", 20);
  font2 = createFont("Waseem", 15);
  
  // buttons
  cp5.addButton("depthUp")
    .setPosition(50, 80) // x and y coordinate of upper left corner of button
    .setSize(160, 80) // (width , height)
    .setFont(font1)
    .setLabel("Depth  Up")
  ;
  
  cp5.addButton("depthDown")
    .setPosition(275, 80) // x and y coordinate of upper left corner of button
    .setSize(160, 80) // (width , height)
    .setFont(font1)
    .setLabel("Depth  Down")
  ;
 
    cp5.addButton("killSwitch")
    .setPosition(165, 550) // x and y coordinate of upper left corner of button
    .setSize(160, 40) // (width , height)
    .setFont(font1)
    .setColorBackground(color(139,0,0)) // color of button
    .setColorForeground(color(255, 0, 0)) // mouse over color
    .setColorActive(color(255, 120, 120)) // color of button depressed
    .setLabel("Kill")
  ;
  
    cp5.addButton("enter")
    .setPosition(208, 220) // x and y coordinate of upper left corner of button
    .setSize(70, 30) // (width , height)
    .setFont(font2)
    .setColorBackground(color(0,122,0)) // color of button
    .setColorForeground(color(0, 180, 0)) // mouse over color
    .setColorActive(color(110, 180, 110)) // color of button depressed
    .setLabel("ENTER")
  ;
    
   cp5.addSlider("Left Servo")
   .setPosition(125,180)
   .setSize(30,130)
   .setRange(1050,1700)
   .setValue(1050)
   ;
   
   cp5.addSlider("Right Servo")
   .setPosition(335,180)
   .setSize(30,130)
   .setRange(1050,1700)
   .setValue(1050)
   ;
   
   cp5.addButtonBar("bar")
   .setPosition(195, 375)
   .setSize(100,30)
   .addItem("manual", '0')
   .addItem("auto", '1')
   ;

   cp5.addToggle("maintainDepth", false)
    .setPosition(305, 440)
    .setSize(20, 20)
    .setMode(ControlP5.SWITCH)
    .setFont(font1)
    .setLabel("")
    ;
    
   cp5.addToggle("maintainRoll", false)
    .setPosition(165, 440)
    .setSize(20, 20)
    .setMode(ControlP5.SWITCH)
    .setFont(font1)
    .setLabel("")
    ;
    
   cp5.addTextlabel("label")
       .setText("AUV/UAV\t\t\t\t\t Test\t\t\t\t\t GUI")
       .setPosition(150, 25)
       .setFont(font1)
      ;    

}

void draw(){ // same as loop in arduino
  
   background(50); // window backgorund color (r,g,b) or (0-255)
   
   //text("AUV/UAV Test GUI", 195, 30); // ("text", x coordinate, y coordinate)

   text("Maintain Roll", 133, 478); // ("text", x coordinate, y coordinate)
   text("OFF", 195, 455);
   text("ON", 135, 455);
 
   text("Maintain Depth", 137+133, 478); // ("text", x coordinate, y coordinate)
   text("OFF", 195+140, 455);
   text("ON", 135+140, 455);
   
  /* Toggle Functions */ 
  
  // maintain current depth position
  if(maintainDepth == true && auto == true){
        if(commandSentDepth == false){
          port.write('e');
          println("maintain Depth ON");
          commandSentDepth = true;
        }
  }else{
        commandSentDepth = false;
      // println("maintain depth turned off");
  }
 
  // maintain current roll position
  if(maintainRoll == true && auto == true){
    if(commandSentRoll == false){
      port.write('m');
      println("maintain Roll ON");
      commandSentRoll = true;
    }
  }else{
      commandSentRoll = false;
  }

  serialEvent(port);
}
