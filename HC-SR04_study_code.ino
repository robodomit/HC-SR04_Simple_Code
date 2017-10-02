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
  #include <math.h>

  #define TRIG_PIN  5   
  #define ECHO_PIN  4   
  #define LED_PIN 13 
  
  float duration, distance;
  float objDistance = 50, knoDistance;
  String strDistance;
  float temp = 29.41; 
  int flag = 2, ind;
  int mm = 1, cal, autocalib = 0;
  float myArray[5];

  void setup() {
    Serial.begin(9600);
       
    pinMode(TRIG_PIN, OUTPUT);  
    pinMode(ECHO_PIN, INPUT); 
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);

    Serial.print("1. Detection distance in centimeters : -> ");
    
    while(Serial.available() == 0) { }  
    objDistance =  Serial.parseFloat ();
    Serial.println(objDistance);
    
    Serial.print("2. Display : integer values (1) or decimal (2) -> ");

    DID:
    while(Serial.available() == 0) { }
    char rep = Serial.read ();
    Serial.println(rep);
    if (rep == '1') {flag = 1;} else  if (rep == '2') {flag = 2;} else {
       Serial.println("wrong option");
       goto DID;      
    }      

    Serial.print("3. Unit : millimeters (m) or centimeters (c) -> "); 

    DMC:  
    while(Serial.available() == 0) { }  
    rep = Serial.read ();
    Serial.println(rep);
    if (rep == 'm') {mm = 10;} else  if (rep == 'c') {mm = 1;} else {
       Serial.println("wrong option");
       goto DMC;      
    }

    Serial.print("4. AutoCalibrate the sensor? : Yes (y) or No (n) ->");

    CAL:  
    while(Serial.available() == 0) { }  
     rep = Serial.read ();
    Serial.println(rep);
    if (rep == 'y') {
       cal = 1;

       Serial.print("4.1. Known distance in centimeters : -> ");
    
       while(Serial.available() == 0) { }  
       knoDistance =  Serial.parseFloat ();
       Serial.println(knoDistance);
       Serial.println("----------------------------------------------");
       return;
    } else  if (rep == 'n') {cal = 2;} else {
       Serial.println("wrong option");
       goto CAL;      
    }   

    Serial.print("5. Select the operating temperature in degrees celsius : 0 (1), 14 (2), 20 (3) 30 (4) -> ");

    SOT:
    while(Serial.available() == 0) { }  
    rep =  Serial.read ();
    Serial.println(rep);
    if (rep == '1') {temp = 30.16;} else if (rep == '2') {temp = 29.41;} else if (rep == '3') {temp = 29.12;} else if (rep == '4') {temp = 28.59;} else {
       Serial.println("wrong option");
       goto SOT;
    }
  } 

  void loop() {   
    float average = 0.00, tempDistance;
    for (int i=0; i <= 100; i++){          
      digitalWrite(TRIG_PIN, LOW);
      delayMicroseconds(4);
      digitalWrite(TRIG_PIN, HIGH);
      delayMicroseconds(10);
      digitalWrite(TRIG_PIN, LOW);
      tempDistance = pulseIn(ECHO_PIN, HIGH, 20000);
      average = average + tempDistance;
      delay(10);
    }  

    duration = average / 100;
    
    if (duration > 0) {
      if (cal == 1) {
        calibrate (duration);
        autocalib++;
        if (autocalib == 10) {
          cal = 2;
          setup;
          Serial.print("Sensor has been calibrated for "); Serial.print(temp); 
          Serial.print(" us/cm with a precision of ");Serial.print(myArray[ind]);
          Serial.println(" cm for the known distance");
        }
        goto fine;
      }
    
      if (flag == 1) {
        distance = (int) round (convertMicrosecondsToDistance (duration, mm, temp));              
      } else if (flag == 2) {
        distance = convertMicrosecondsToDistance (duration, mm, temp);
      }

      if (mm == 1) {Serial.print("Distance in centimeters : ");} else if (mm == 10) {Serial.print("Distance in millimeters : ");} 
      if (flag == 1) {strDistance = String(distance, 0);} else if (flag == 2) {strDistance = String(distance, 2);}
      Serial.println(strDistance);  
      
      if (distance < objDistance * mm) {
        digitalWrite(LED_PIN, HIGH);
        Serial.print("  Obstacle at a distance of ");
        Serial.println(strDistance);
      } else {
        digitalWrite(LED_PIN, LOW);
      }
    }
    delay(200);
    fine:;
  }

  float convertMicrosecondsToDistance(float microseconds, int unit, float speedOftemp) {    
    return (microseconds / 2 / speedOftemp) * unit;
  }

  void calibrate (float micro) {        
     float tmpDist, spdArray[5], tmpSpeed = 28.00;

     for (int i=0; i<= 4; i++) {
        tmpDist = (micro / 2 / tmpSpeed) * 1;
        Serial.print(tmpDist); Serial.print(" | ");
        spdArray[i] = tmpSpeed;
        if (tmpDist>knoDistance){ myArray[i] = tmpDist - knoDistance;} else {myArray[i] = knoDistance - tmpDist;}
        tmpSpeed = tmpSpeed + 0.5;
     }
      Serial.print(" | > "); Serial.println(knoDistance);

     for (int i=0; i< 4; i++) {
        Serial.print(myArray[i]); Serial.print(" | ");
     }
     Serial.print(myArray[4]);  

     ind = getIndexOfMinimumValue(myArray, 5); 
     Serial.print(" | > "); Serial.println(ind);
     temp = spdArray[ind];
     return;
  }

  int getIndexOfMinimumValue(float myArrayF[5], int sizeF){
     int minIndex = 0;
     float minim = myArrayF[minIndex];
     for (int i=1; i<sizeF; i++){
        if (minim>myArrayF[i]){
           minim = myArrayF[i];
           minIndex = i;
        }
     }
     return minIndex;
  }
