#include <Servo.h>

#define TURN_TIME 2000

Servo myservo;

void setup() {
    myservo.attach(2);
    // Initially the servo must be stopped 
    myservo.write(90);


   // Start turning clockwise
    myservo.write(180);
    delay(5000);
  myservo.write(0);
  delay(5000);
  myservo.write(90);
    
    
    // Go on turning for the right duration
  //  delay(TURN_TIME);
    // Stop turning
    //myservo.write(90);



    
}

void loop() {
 

}
