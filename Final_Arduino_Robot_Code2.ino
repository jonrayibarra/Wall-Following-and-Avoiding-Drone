#include <AFMotor.h>
int echo_left=13; //echo_front
int trig_left=12;
int echo_right=9; //echo_left
int trig_right=8;
// delete echo_right
AF_DCMotor motor1(1,MOTOR12_64KHZ);
AF_DCMotor motor2(2, MOTOR12_8KHZ);

//long time_front,distance_front,minimum_front,distance_left,minimum_left,time_left,distance_right,minimum_right,time_right;
  
long time_left,distance_left,minimum_left,distance_right,minimum_right,time_right;

void setup()
{
  Serial.begin(9600);
  pinMode(trig_left,OUTPUT);
  pinMode(echo_left,INPUT);
  pinMode(trig_right,OUTPUT);
  pinMode(echo_right,INPUT);
}

void loop() 
{
    sensor_left();
    sensor_right();
    forward_robot();
    Serial.println("Robot Forward");
    
    if(distance_left<=minimum_left)
    {
       tern_left();
    
    }
    if(distance_right<=minimum_right)
    {
      tern_right();
    }
    if(distance_left<=minimum_left && distance_right<=minimum_right)
    {
      if(distance_left==2 && distance_right==2){
        backward_robot();
        delay(2000);
      }
        forward_robot();
        //stop_robot();
      }
    delay(50);
}

void sensor_left()
{
digitalWrite(trig_left, LOW); 
delayMicroseconds(2);
digitalWrite(trig_left, HIGH); 
delayMicroseconds(20);
digitalWrite(trig_left, LOW);
 
time_left=pulseIn(echo_left,HIGH);
distance_left=time_left/58.2;
minimum_left=7;    
}

void sensor_right()
{
digitalWrite(trig_right, LOW); 
delayMicroseconds(2);
digitalWrite(trig_right, HIGH); 
delayMicroseconds(20);
digitalWrite(trig_right, LOW);
 
time_right=pulseIn(echo_right,HIGH);
distance_right=time_right/58.2;
minimum_right=7; 
}

void forward_robot()
{
  motor1.setSpeed(135); //set the speed of the motors, between 0-255
  motor2.setSpeed (135);
  motor1.run(FORWARD);
  motor2.run (BACKWARD);
}

void backward_robot()
{
  motor2.setSpeed (115);
  motor1.run(BACKWARD);
  motor2.run (FORWARD);
}
/*void stop_robot()
{
  // slow down
  motor1.setSpeed(115); //set the speed of the motors, between 0-255
  motor2.setSpeed (115);
  motor1.run(FORWARD);  // Turn as long as there's an obstacle ahead.
  motor2.run (BACKWARD);
}*/

void tern_left()
{
  //motor1.setSpeed(100); //set the speed of the motors, between 0-255
  //motor2.setSpeed (115);
  motor1.run(FORWARD);  // Turn as long as there's an obstacle ahead.
  motor2.run (FORWARD);
}

void tern_right()
{
  //motor1.setSpeed(115); //set the speed of the motors, between 0-255
  //motor2.setSpeed (100);
  motor1.run(BACKWARD);  // Turn as long as there's an obstacle ahead.
  motor2.run (BACKWARD);
}

