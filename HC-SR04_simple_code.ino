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

#define TRIG_PIN  5   // Trig - green Wire  
#define ECHO_PIN  4   // Echo - blue Wire      

void setup() {
  Serial.begin(115200);
  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);    
} 

void loop() { 
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(4);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  float microseconds = pulseIn(ECHO_PIN, HIGH);
  float cm = (microseconds / 2) / 29.12;
  float in = (microseconds / 2) / 74;  
  Serial.print("Distance in centimeters : ");  
  Serial.println(cm);  
  Serial.print("Distance inches : ");  
  Serial.println(in);
  delay(500);
}

