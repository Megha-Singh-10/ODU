#include <Servo.h>
#include <math.h>

#define in1 5 //L298n Motor Driver pins.
#define in2 6
#define in3 3
#define in4 9
#define speed 255

// Defines Tirg and Echo pins of the Ultrasonic Sensor
const int trigPin = 10;
const int echoPin = 11;
// Variables for the duration and the distance
long duration;
Servo myServo; // Creates a servo object for controlling the servo motor

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600);
  myServo.attach(12); // Defines on which pin is the servo motor attached
}
void loop() {
  float d1=0,d2, a1=0,a2;
  float distance, angle;
  unsigned long t1=0,t2;
  float myposx=0, myposy=0, myvelo=1.25;
	
	
 /* for(int a1=0;a1<=359;a1++){ 
  myServo.write(angle);
  d1 = calculateDistance();
  t1= millis();
  delay(5);
  }*/
  
  for(a2=0;a2<=359;a2++){  
  myServo.write(angle);
  d2 = calculateDistance();
  t2= millis();
  delay(5);
  }
	
  predict(d1,a1,t1, d2,a2,t2, &distance, &angle);  //now the distance and angle of predicted pt. is stored in distance and angle variables
  
  if(angle==0)                    right();
  else if(angle>0 || angle<90)    forwardright(angle);
  else if(angle==90)              forward();
  else if(angle>90 || angle<180)  forwardleft(angle);
  else if(angle==180)             left();
  else if(angle>180 || angle<270) backwardleft(angle);
  else if(angle==270)             backward();
  else if(angle>270 || angle<360) backwardright(angle);
	
	
	//code to start moving to pt (distance,angle)-----------------------------------------------------------------------
	
  d1=d2; a1=a2; 
	
}
// Function for calculating the distance measured by the Ultrasonic sensor
int calculateDistance(){ 
  
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  distance= duration*0.034/2;
  return distance;
}

void predict(float d1, float a1, unsigned long t1, float d2, float a2, unsigned long t2, float* distance, float* angle)
{
	float pi=3.14159265359;
	a1= a1*pi/180; //conversion to radians
	a2= a2*pi/180;
	
	float x1= d1*cos(a1);
	float y1= d1*sin(a1);
	
	float x2= d2*cos(a2);
	float y2= d2*sin(a2);
	
	float m= (y2-y1)/(x2-x1);
	
	float v= (sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1)))/(t2-t1);
	
	float d= v*1800; //distance travelled after 1800 milli seconds with velocity V.
	
	float A= 1+m*m;
	float B= -2*x2-m*m*2*x1+2*m*(y1-y2);
	float C= x2*x2+m*m*x1*x1+(y1-y2)*(y1-y2)-2*m*x1*(y1-y2)-d*d;
	
	float solx1= (-B+sqrt(B*B-4*A*c))/(2*A);
	float solx2= (-B-sqrt(B*B-4*A*c))/(2*A);
	
	float soly1= m*(solx1-x1)+y1;
	float soly2= m*(solx2-x1)+y1;
	
	float X,Y;
	
	if(sqrt((solx1-x1)*(solx1-x1)+(soly1-y1)*(soly1-y1)) > sqrt((solx2-x1)*(solx2-x1)+(soly2-y1)*(soly2-y1)) ) //finding the pt further to the (x1,y1) 
	{ X=solx1; Y=soly1; }
	
	else { X=solx2; Y=soly2; }
	
	float *distance= sqrt(X*X+Y*Y);
	float *angle= atan(Y/X)*180/pi; //atan= tan inverse and radians are converted to degrees.
	
}

/*vpid moveMeTo(float* fromd, float* froma, flaot tod, float toa, float v)
{
	flaot myd = *fromd; float mya = *froma;
	
	float pi=3.14159265359;
	
	mya = mya*pi/180; //conversion to radians
	toa = toa*pi/180;
	
	float x2= myd*cos(mya); //here x1,y1 are destination coordinates and x2,y2 are source coordinates.
	float y2= myd*sin(mya);
	
	float x1= tod*cos(toa);
	float y1= tod*sin(toa);
	
	float m= (y2-y1)/(x2-x1);
	float d= v*1800; //distance travelled by the chaser in 1800.
	
	float A= 1+m*m;
	float B= -2*x2-m*m*2*x1+2*m*(y1-y2);
	float C= x2*x2+m*m*x1*x1+(y1-y2)*(y1-y2)-2*m*x1*(y1-y2)-d*d;
	
	float solx1= (-B+sqrt(B*B-4*A*c))/(2*A);
	float solx2= (-B-sqrt(B*B-4*A*c))/(2*A);
	
	float soly1= m*(solx1-x1)+y1;
	float soly2= m*(solx2-x1)+y1;
	
	float X,Y;
	
	if(sqrt((solx1-x1)*(solx1-x1)+(soly1-y1)*(soly1-y1)) > sqrt((solx2-x1)*(solx2-x1)+(soly2-y1)*(soly2-y1)) ) //finding the pt further to the (x1,y1) 
	{ X=solx1; Y=soly1; }
	
	else { X=solx2; Y=soly2; }
	
	float *distance= sqrt(X*X+Y*Y);
	float *angle= atan(Y/X)*180/pi; //atan= tan inverse and radians are converted to degrees.
}
*/

void forward() {
  analogWrite(in1, Speed);
  analogWrite(in3, Speed);
}

void back() {
  analogWrite(in2, Speed);
  analogWrite(in4, Speed);
}

void left() {
  analogWrite(in3, Speed);
  analogWrite(in2, Speed);
}

void right() {
  analogWrite(in4, Speed);
  analogWrite(in1, Speed);
}
void forwardleft() {
  analogWrite(in1, Speed);
  analogWrite(in3, Speed);
}
void forwardright() {
  analogWrite(in1, Speed);
  analogWrite(in3, Speed);
}
void backright() {
  analogWrite(in2, Speed);
  analogWrite(in4, Speed);
}
void backleft() {
  analogWrite(in2, Speed);
  analogWrite(in4, Speed);
}














