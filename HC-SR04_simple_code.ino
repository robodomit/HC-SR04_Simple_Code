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
long duration, distance_cm, distance_in;     

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
  duration = pulseIn(ECHO_PIN, HIGH);
  distance_cm = convertMicroTo (duration, 1);
  distance_in = convertMicroTo (duration, 2);
  Serial.print("Distance in centimeters : ");  
  Serial.println(distance_cm);  
  Serial.print("Distance in inches : ");  
  Serial.println(distance_in);
  delay(900);
}

long convertMicroTo (long microseconds, int unit) {
       // The speed of sound is 343,4 m/s at 20 degrees celsius or 29,12 microseconds per centimeter.
       // The ping travels out and back, so to find the distance of the object we take half of the distance travelled.
       // For inches you have to convert by formula in = m * 39,370
       // 74,70 microseconds per inch (i.e. sound travels at 1130 feet per
       // second).  This gives the distance travelled by the ping, outbound
       // and return, so we divide by 2 to get the distance of the obstacle.
  if (unit == 1) {       
    return microseconds / 2 / 29.12;  
  } else if (unit == 2) {
    return microseconds / 2 / 74.70;
  } else {
       
  }
}

