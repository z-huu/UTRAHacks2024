//Includes the Arduino Stepper Library
/*#include <Stepper.h>

// Defines the number of steps per rotation
const int stepsPerRevolution = 2038;

// Creates an instance of stepper class
// Pins entered in sequence IN1-IN3-IN2-IN4 for proper step sequence
Stepper myStepper = Stepper(stepsPerRevolution, 8, 10, 9, 11);

void setup() {
    // Nothing to do (Stepper Library sets pins as outputs)
}

void loop() {
	// Rotate CW slowly at 5 RPM
	myStepper.setSpeed(5);
	myStepper.step(stepsPerRevolution);
	delay(1000);
	
	// Rotate CCW quickly at 10 RPM
	myStepper.setSpeed(10);
	myStepper.step(-stepsPerRevolution);
	delay(1000);
}*/
/*
#include <Servo.h>
Servo servo;
int angle = 10;
void setup() {
  servo.attach(8);
  servo.write(angle);
}
void loop() 
{ 
 // scan from 0 to 180 degrees
  for(angle = 10; angle < 180; angle++)  
  {                                  
    servo.write(angle);               
    delay(15);                   
  } 
  // now scan back from 180 to 0 degrees
  for(angle = 180; angle > 10; angle--)    
  {                                
    servo.write(angle);           
    delay(15);       
  } 
}
*/

#include <math.h>

int motor1pin1 = 6;
int motor1pin2 = 7;

int motor2pin1 = 5;
int motor2pin2 = 4;

int lastVal14 = 0;
int lastVal15 = 0;
int lastVal16 = 0;

int delta14 = 0;
int delta15 = 0;
int delta16 = 0;

void setup() {
// put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);

  //(Optional)
  pinMode(9, OUTPUT); 
  pinMode(10, OUTPUT);
  //pinMode(3, INPUT);
  pinMode(14, INPUT);
  pinMode(15, INPUT);
  pinMode(16, INPUT);
  pinMode(17, INPUT);
  //(Optional)
}

void loop() {
   // put your main code here, to run repeatedly:

  //Controlling speed (0   = off and 255 = max speed):     
  //(Optional)
  
  //(Optional)
  int max = 14;
  for(int i = 15; i < 17; i++) {
    if (max == 14) {
      if (analogRead(i) > analogRead(max) * 0.39) { // might be TOO sensitive
        max = i;
      }
    } else {
      if (analogRead(i) > analogRead(max)) {
      max = i;
    }
    }
  }

  Serial.println(max);
/*
  if (analogRead(14) + delta15 > 0 && analogRead(14) + delta16 < 0) {
    digitalWrite(motor1pin1,   LOW);
    digitalWrite(motor1pin2, HIGH);

    digitalWrite(motor2pin1, HIGH);
    digitalWrite(motor2pin2, LOW);

  } else if (analogRead(14) + delta15 < 0 && analogRead(14) + delta16 > 0) {
    digitalWrite(motor1pin1,   HIGH);
    digitalWrite(motor1pin2, LOW);

    digitalWrite(motor2pin1, LOW);
    digitalWrite(motor2pin2, HIGH);
  } else {
    digitalWrite(motor1pin1,   HIGH);
    digitalWrite(motor1pin2, LOW);

    digitalWrite(motor2pin1, HIGH);
    digitalWrite(motor2pin2, LOW);
  }
  */

  if (max == 15) {
    digitalWrite(motor1pin1,   HIGH);
    digitalWrite(motor1pin2, LOW);

    digitalWrite(motor2pin1, LOW);
    digitalWrite(motor2pin2, HIGH);
    //analogWrite(9, (analogRead(14) + delta14 + delta15 + 60 + analogRead(15)) *3);
    //analogWrite(10, (analogRead(14) + delta14) * 3);

    analogWrite(9, 255);
    analogWrite(10, 255);

    //Serial.print(pow(abs(analogRead(14) + delta14 + delta15 + 20 + analogRead(15)), 2));
    //Serial.print(" ");
    //Serial.println(pow(abs(analogRead(14) + delta14 + delta16), 2));
  } else if (max == 16) {
    digitalWrite(motor1pin1,   LOW);
    digitalWrite(motor1pin2, HIGH);

    digitalWrite(motor2pin1, HIGH);
    digitalWrite(motor2pin2, LOW);
    //analogWrite(9, (analogRead(14) + delta14) * 3);
    //analogWrite(10, (analogRead(14) + delta14 + delta16 + 60 + analogRead(16)/2) * 3);
    analogWrite(9, 255);
    analogWrite(10, 255);

    //Serial.print(pow(abs(analogRead(14) + delta14 + delta15), 2));
    //Serial.print(" ");
    //Serial.println(pow(abs(analogRead(14) + delta14 + delta16 + 20 + analogRead(16)/2), 2));
  } else {
    digitalWrite(motor1pin1,   HIGH);
    digitalWrite(motor1pin2, LOW);

    digitalWrite(motor2pin1, HIGH);
    digitalWrite(motor2pin2, LOW);
    if ((analogRead(14) + delta14 + delta15 + 20) * 2 > 255) {
      analogWrite(9, 255);
    } else {
      analogWrite(9, (analogRead(14) + delta14 + delta15 + 20) * 2);
    }
    
    if ((analogRead(14) + delta14 + delta16 + 20) * 2 > 255) {
      analogWrite(10, 255);
    } else {
      analogWrite(10, (analogRead(14) + delta14 + delta16 + 20) * 2); // ADJUST THESE MAYBE!
    }

    //analogWrite(9, 255);
    //analogWrite(10, 255);

    Serial.print((analogRead(14) + delta14 + delta15 + 20) * 2);
    Serial.print(" ");
    Serial.println((analogRead(14) + delta14 + delta16 + 20) * 2);
  }

  /*
  if(analogRead(max) >= 585) {
    // vibe
  } else if (max == 14) {
    analogWrite(9, 1000); //ENA   pin
    analogWrite(10, 1000); //ENB pin
    digitalWrite(motor1pin1,   HIGH);
    digitalWrite(motor1pin2, LOW);

    digitalWrite(motor2pin1, HIGH);
    digitalWrite(motor2pin2, LOW);
  } else if (max == 15) {
    analogWrite(9, 1000); //ENA   pin
    analogWrite(10, 1000); //ENB pin
    digitalWrite(motor1pin1,   HIGH);
    digitalWrite(motor1pin2, LOW);

    digitalWrite(motor2pin1, LOW);
    digitalWrite(motor2pin2, HIGH);
  } else if (max == 16) {
    analogWrite(9, 1000); //ENA   pin
    analogWrite(10, 1000); //ENB pin
    digitalWrite(motor1pin1,   LOW);
    digitalWrite(motor1pin2, HIGH);

    digitalWrite(motor2pin1, HIGH);
    digitalWrite(motor2pin2, LOW);
  }
  */
  delay(300);
  Serial.print("ALL OF THE DELTAS: ");
  Serial.print(delta15);
  Serial.print(" ");
  Serial.print(delta14);
  Serial.print(" ");
  Serial.println(delta16);

  delta14 = (analogRead(14) - lastVal14) * 0.6;
  delta15 = analogRead(15) - lastVal15;
  delta16 = pow(analogRead(16) - lastVal16, 1.05);

  lastVal14 = analogRead(14);
  lastVal15 = analogRead(15);
  lastVal16 = analogRead(16);

  Serial.println(analogRead(17) / 1023.0 * 3.3); // POTENTIAL STOP CONDITION: READ VOLTAGE ACROSS SOLAR DIODE (once Vt is hit, shut off car)
}