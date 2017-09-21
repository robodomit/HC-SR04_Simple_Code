/*
 * created by Doru Mandache, http://robodomit.blogspot.ro
 * 
 * Hardware Connections:
        HC-SR04 | Arduino   
      ----------------------------------------
         VCC    |  +5V
         GND    |  GND (any GND pin)
         Trig   |  Pin 5 or any digital pins
         Echo   |  Pin 4 or any digital pins
 */

#define TRIG_PIN  5   // Trig - green Wire in my project 
#define ECHO_PIN  4   // Echo - blue Wire in my project 
float microseconds;
float distance_cm, distance_inch;     

void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);  
  pinMode(ECHO_PIN, INPUT);    
} 

void loop() { 
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(4);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  microseconds = pulseIn(ECHO_PIN, HIGH);
  convertMicroTo ();
  Serial.print("Distance in centimeters : ");  
  Serial.println(distance_cm);  
  Serial.print("Distance in inches : ");  
  Serial.println(distance_inch);
  delay(500);
}

void convertMicroTo () {
    return distance_cm = (microseconds / 2) / 29.12;  
    return distance_inch = (microseconds / 2) / 74; 
}

