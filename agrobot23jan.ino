float pingtime;
float distance;
float speedofsound;

int frontTrig = 13;   //ultrasonic pins
int frontEcho = 3;
int leftEcho = 11;
int leftTrig = 10;
int rightEcho = 9;
int rightTrig = 8;

const int motorL1 = 2;
const int motorL2 = 3;
const int motorR1 = 4;
const int motorR2 = 5;

float frontPingTime, frontDistanceinch, rightDistanceinch, rightPingTime, leftPingTime, leftDistanceinch;
void setup() {
  // put your setup code here, to run once:
  
Serial.begin(9600);
speedofsound=13503.937;

pinMode(frontTrig,OUTPUT); 
pinMode(frontEcho,INPUT);
pinMode(rightTrig,OUTPUT); 
pinMode(rightEcho,INPUT);
pinMode(leftTrig,OUTPUT); 
pinMode(leftEcho,INPUT);

pinMode(motorL1, OUTPUT); //motors
pinMode(motorL2, OUTPUT);
pinMode(motorR1, OUTPUT);
pinMode(motorR2, OUTPUT);

}

void loop() {
  
//checking the obstacle at front
  FrontDist();
  if (frontDistanceinch < 5) {
    Serial.println("OBSTACLE!!");
    LeftDist();
    delay(20);
    RightDist();
    delay(20);
    if (leftDistanceinch < rightDistanceinch){
      moveRight();
      delay(4000);
      Stop();
      delay(2000);
    }
    else if (leftDistanceinch > rightDistanceinch) {
      moveLeft();
      delay(4000);
      Stop();
      delay(2000);
    }
  }
  else {
    Serial.println("OK");
    moveForward();
    delay(4000);
    Stop();
    delay(2000);
  }
  
  // checking obstacle left side
  LeftDist();
  if (leftDistanceinch < 5) {
    Serial.println("Left obstacle...");
    delay(20);
    LeftDist();
    delay(20);
    RightDist();
    delay(20);
    if (leftDistanceinch > rightDistanceinch){
      moveForward();
      delay(4000);
      Stop();
      delay(2000);
    }
    else if (leftDistanceinch < rightDistanceinch) {
      moveRight();
      delay(4000);
      Stop();
      delay(2000);
    }
  }
  
  // checking obstacle right side
  RightDist();
  if (rightDistanceinch < 5) {
    Serial.println("Right obstacle...");
    delay(20);
    RightDist();
    delay(20);
    LeftDist();
    delay(20);
    if (rightDistanceinch > leftDistanceinch){
      moveForward();
      delay(4000);
      Stop();
      delay(2000);
    }
    else if (rightDistanceinch < leftDistanceinch) {
      moveLeft();
      delay(4000);
      Stop();
      delay(2000);
    }
  }
}



void FrontDist() {
  digitalWrite(frontTrig, LOW);  
  delayMicroseconds(4);
  digitalWrite(frontTrig, HIGH);  
  delayMicroseconds(10);
  digitalWrite(frontTrig, LOW);
  frontPingTime = pulseIn(frontEcho, HIGH);  
  frontPingTime = frontPingTime/1000000;
  frontDistanceinch = frontPingTime * speedofsound;
  frontDistanceinch = frontDistanceinch/2; 
    
  Serial.print("Distance: ");
  Serial.print(frontDistanceinch);
  Serial.println(" inches");
}
void LeftDist() {
  digitalWrite(leftTrig, LOW);  
  delayMicroseconds(4);
  digitalWrite(leftTrig, HIGH);  
  delayMicroseconds(10);
  digitalWrite(leftTrig, LOW);
  leftPingTime = pulseIn(leftEcho, HIGH);  
  leftPingTime = leftPingTime/1000000;
  leftDistanceinch = leftPingTime * speedofsound;
  leftDistanceinch = leftDistanceinch/2; 
   
  Serial.print("Left distance: ");
  Serial.print(leftDistanceinch);
  Serial.println(" inches");
}
void RightDist() {
  digitalWrite(rightTrig, LOW);  
  delayMicroseconds(4);
  digitalWrite(rightTrig, HIGH);  
  delayMicroseconds(10);
  digitalWrite(rightTrig, LOW);
  rightPingTime = pulseIn(rightEcho, HIGH);  
  rightPingTime = rightPingTime/1000000;
  rightDistanceinch = rightPingTime * speedofsound;
  rightDistanceinch = rightDistanceinch/2; 
  
  Serial.print("Right distance: ");
  Serial.print(rightDistanceinch);
  Serial.println(" inches");
}
void moveBackward() {
  Serial.println("Backward.");
  digitalWrite(motorL1, HIGH);
  digitalWrite(motorL2, LOW);
  digitalWrite(motorR1, HIGH);
  digitalWrite(motorR2, LOW);
}
void moveForward() {
  Serial.println("Forward.");
  digitalWrite(motorL1, LOW);
  digitalWrite(motorL2, HIGH);
  digitalWrite(motorR1, LOW);
  digitalWrite(motorR2, HIGH);
}
void moveLeft() {
  Serial.println("Left.");
  digitalWrite(motorL1, LOW);
  digitalWrite(motorL2, HIGH);
  digitalWrite(motorR1, HIGH);
  digitalWrite(motorR2, LOW);
}
void moveRight() {
  Serial.println("Right.");
  digitalWrite(motorL1, HIGH);
  digitalWrite(motorL2, LOW);
  digitalWrite(motorR1, LOW);
  digitalWrite(motorR2, HIGH);
}
void Stop() {
  Serial.println("Stop. ");
  digitalWrite(motorL1, LOW);
  digitalWrite(motorL2, LOW);
  digitalWrite(motorR1, LOW);
  digitalWrite(motorR2, LOW);
}
