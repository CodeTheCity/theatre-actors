// Sensor stuff
const int trigPin = 25;
const int echoPin = 23;

long duration;
int distance;

// Lights
int ledPin1 = 8;
int ledPin2 = 7;


// Motor stuff
int motor1Pin1 = 53; // Brown
int motor1Pin2 = 51; // Red
int motor1Pin3 = 49; // Orange
int motor1Pin4 = 47; // Yellow

int motor2Pin1 = 45; // Brown
int motor2Pin2 = 43; // Red
int motor2Pin3 = 41; // Orange
int motor2Pin4 = 39; // Yellow

int motor3Pin1 = 37; // Brown
int motor3Pin2 = 35; // Red
int motor3Pin3 = 33; // Orange
int motor3Pin4 = 31; // Yellow


int motorSpeed = 1000; //1200; // variable to set stepper speed
int count = 0; // count of steps made
int countsperrev = 512; //2048; // number of steps per full revolution
int lookup[8] = {B01000, B01100, B00100, B00110, B00010, B00011, B00001, B01001};
int act = 0;

void setup() {
  // setup sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // setup light pins
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  
  // declare the motor pins as outputs
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor1Pin3, OUTPUT);
  pinMode(motor1Pin4, OUTPUT);
  
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(motor2Pin3, OUTPUT);
  pinMode(motor2Pin4, OUTPUT);
  
  pinMode(motor3Pin1, OUTPUT);
  pinMode(motor3Pin2, OUTPUT);
  pinMode(motor3Pin3, OUTPUT);
  pinMode(motor3Pin4, OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  
//  return;
  
  // Clear the trig pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Clear the light pins
  digitalWrite(ledPin1, LOW);
  
  // Sets the trig pin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echo pin, returns the sound wave travel tie in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  distance = duration * 0.034 / 2;
  
  Serial.print("Distance (cm): ");
  Serial.println(distance);
  
  if ( distance >= 0 && distance < 200 ) {
    motorSpeed = ( 800 + ( distance * 25 ) < 1000 ? 1000 : 1000 + ( distance * 25 ) );
    Serial.print("Distance detected: ");
    Serial.println(distance);
    Serial.print("Speed set: ");
    Serial.println(motorSpeed);
  } else {
    Serial.println("No proximity");
  }
  
//  return;
  
  // Start the show if movement less than 10cm from the sensor
  if(act == 0 && distance < 40 && distance > 0) {
    act = 1;
  }
  
  if(act == 1) {
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, HIGH);
    if(count < countsperrev ) {
      clockwise(3);
            anticlockwise(2);

      clockwise(1);
      
    } else if(count == countsperrev * 2) {
      digitalWrite(ledPin1, LOW);
      digitalWrite(ledPin2, LOW);
      count = 0;
      act = 0;
    } else {
      anticlockwise(3);
            clockwise(2);

      anticlockwise(1);
      
      
      //clockwise(1);
      //clockwise(2);
      //clockwise(3);
    }
    count++;
  }
 
}

// Set pins to ULN2003 high in sequene from 1 to 4
// delay "motorSpeed" between each pin setting (to deterimine speed)
void anticlockwise(int motor) {
  for(int i = 0; i < 8; i++) {
    setOutput(i, motor);
//    setOutput(i, 2);
//    setOutput(i, 3);
      delayMicroseconds(motorSpeed);
  }
}

void clockwise(int motor) {
  for(int i = 7; i >= 0; i--) {
    setOutput(i, motor);
//    setOutput(i, 2);
//    setOutput(i, 3);
      delayMicroseconds(motorSpeed);
  }
}

void setOutput(int out, int motor) {
  if (motor == 1) 
  {
    digitalWrite(motor1Pin1, bitRead(lookup[out], 0));
    digitalWrite(motor1Pin2, bitRead(lookup[out], 1));
    digitalWrite(motor1Pin3, bitRead(lookup[out], 2));
    digitalWrite(motor1Pin4, bitRead(lookup[out], 3));
  }
  
  if (motor == 2) 
  {
    digitalWrite(motor2Pin1, bitRead(lookup[out], 0));
    digitalWrite(motor2Pin2, bitRead(lookup[out], 1));
    digitalWrite(motor2Pin3, bitRead(lookup[out], 2));
    digitalWrite(motor2Pin4, bitRead(lookup[out], 3));
  }
  
  if (motor == 3) 
  {
    digitalWrite(motor3Pin1, bitRead(lookup[out], 0));
    digitalWrite(motor3Pin2, bitRead(lookup[out], 1));
    digitalWrite(motor3Pin3, bitRead(lookup[out], 2));
    digitalWrite(motor3Pin4, bitRead(lookup[out], 3));
  }
}
