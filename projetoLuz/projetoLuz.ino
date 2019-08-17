/* 
DESCRIPTION
====================
Reports through serial (57600 baud) the time since 
a button press (transition from HIGH to LOW).

*/

// Include the Bounce2 library found here :
// https://github.com/thomasfredericks/Bounce2
#include <Bounce2.h>


//------IR
#include <RCSwitch.h>
RCSwitch mySwitch = RCSwitch();
#define CODBT1 -25646
#define CODBT2 -25647
int COD = 0;

//------IR


#define BUTTON_PIN 3
#define BUTTON_PIN2 4 
#define BUTTON_PIN3 7





// Instantiate a Bounce object :
Bounce debouncer = Bounce();
Bounce debouncer2 = Bounce(); 
Bounce debouncer3 = Bounce(); 
int d = 0;


unsigned long buttonPressTimeStamp;


//--- RELEY
const int relayPin = 5;
const int relayPin2 = 6;
//--- RELEY

void setup() {

//--- RELEY
pinMode(relayPin, OUTPUT);
pinMode(relayPin2, OUTPUT);
digitalWrite(relayPin, HIGH);
digitalWrite(relayPin2, HIGH);


//--- RELEY
  

//------IR

 mySwitch.enableReceive(0);
//------IR
  
  
  Serial.begin(9600);

  Serial.println("iniciando");
  
  // Setup the button with an internal pull-up :
  pinMode(BUTTON_PIN,INPUT_PULLUP);
  pinMode(BUTTON_PIN2,INPUT_PULLUP);
  pinMode(BUTTON_PIN3,INPUT_PULLUP);
  
  // After setting up the button, setup the Bounce instance :
  debouncer.attach(BUTTON_PIN);
  debouncer2.attach(BUTTON_PIN2);
  debouncer3.attach(BUTTON_PIN3);
  debouncer.interval(5);
  debouncer2.interval(5);
  debouncer3.interval(5);
  

  
}

void loop() {
  
   // Update the Bounce instance :
  debouncer.update();
  debouncer2.update();
  debouncer3.update();

  // Call code if Bounce fell (transition from HIGH to LOW) :
  if ( debouncer.fell()  ) {;
  
   // Serial.println( millis()-buttonPressTimeStamp );
    if ( (millis()-buttonPressTimeStamp) > 100 ){
      bt1();
    }
       
     buttonPressTimeStamp = millis();
  
  }

   // Call code if Bounce fell (transition from HIGH to LOW) :
  if ( debouncer2.fell()  ) {;
  
   // Serial.println( millis()-buttonPressTimeStamp );
    if ( (millis()-buttonPressTimeStamp) > 100 ){
      bt2();
    }
       
     buttonPressTimeStamp = millis();
  
  }

  // Call code if Bounce fell (transition from HIGH to LOW) :
  if ( debouncer3.fell()  ) {;
  
   // Serial.println( millis()-buttonPressTimeStamp );
    if ( (millis()-buttonPressTimeStamp) > 100 ){
      bt3();
    }
       
     buttonPressTimeStamp = millis();
  
  }



//------IR
  if (mySwitch.available()) {
    
    int value = mySwitch.getReceivedValue();
    
    if (value == 0) {
      Serial.print("Unknown encoding");
    } else {
      //Serial.print("Received ");


      
      //Serial.print( mySwitch.getReceivedValue() );


      COD = mySwitch.getReceivedValue();
     // Serial.println(COD);
      if(COD == CODBT1){
        bt1();
      }
            
      if(COD == CODBT2){
        bt2();
      }
      
      
      //Serial.print(" / ");
      //Serial.print( mySwitch.getReceivedBitlength() );
      //Serial.print("bit ");
      //Serial.print("Protocol: ");
      //Serial.println( mySwitch.getReceivedProtocol() );
    }

    mySwitch.resetAvailable();
  }
//------IR

}

void bt1() {
  Serial.println("Ok - BT1"); 
  digitalWrite(relayPin, !digitalRead(relayPin));
}
void bt2() {
  Serial.println("Ok - BT2"); 
  digitalWrite(relayPin2, !digitalRead(relayPin2));
}

void bt3() {
  Serial.println("Ok - BT3");
   
  digitalWrite(relayPin,  !digitalRead(relayPin));
  digitalWrite(relayPin2, digitalRead(relayPin));
}
