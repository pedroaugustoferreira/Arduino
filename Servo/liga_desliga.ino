/* 
DESCRIPTION
====================
Reports through serial (57600 baud) the time since 
a button press (transition from HIGH to LOW).

*/

// Include the Bounce2 library found here :
// https://github.com/thomasfredericks/Bounce2
#include <Bounce2.h>
#include <Servo.h>


#define BUTTON_PIN 2
#define SERVO_PIN 4

// Instantiate a Bounce object :
Bounce debouncer = Bounce(); 
Servo myservo;
int d = 0;

unsigned long buttonPressTimeStamp;

void setup() {
  
  Serial.begin(9600);

  Serial.println("iniciando");

    myservo.attach(SERVO_PIN);
    // Initially the servo must be stopped 
    myservo.write(90);

  
  // Setup the button with an internal pull-up :
  pinMode(BUTTON_PIN,INPUT_PULLUP);
  
  // After setting up the button, setup the Bounce instance :
  debouncer.attach(BUTTON_PIN);
  debouncer.interval(5);
  

  
}

void loop() {
  
   // Update the Bounce instance :
  debouncer.update();

  // Call code if Bounce fell (transition from HIGH to LOW) :
  if ( debouncer.fell()  ) {;
  
   // Serial.println( millis()-buttonPressTimeStamp );
    if ( (millis()-buttonPressTimeStamp) > 100 ){
      if ( d == 0 ){
        myservo.write(180);
        d = 1;
      }else if ( d == 1 ){
        myservo.write(90);
        d = 2;
      }else if ( d == 2 ){
        myservo.write(0);
        d = 3;
      }else if ( d == 3 ){
        myservo.write(90);
        d = 0;
      }
      
      Serial.println("Ok"); 
    }
       
     buttonPressTimeStamp = millis();
  
  }
  

}
