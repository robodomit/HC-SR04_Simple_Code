#define PIN_RELEU_1  7
#define PIN_RELEU_2  4
#define ECHOPIN 6        // Pin to receive echo pulse
#define TRIGPIN 5        // Pin to send trigger pulse

int stare_releu=0;

void setup() {
    Serial.begin(115200);
    pinMode(PIN_RELEU_1, OUTPUT);
    pinMode(PIN_RELEU_2, OUTPUT);
    pinMode(ECHOPIN, INPUT);
    pinMode(TRIGPIN, OUTPUT);
}

void loop() {
  digitalWrite(TRIGPIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGPIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGPIN, LOW);
  
  float distance = pulseIn(ECHOPIN, HIGH);
  distance= distance/58;
  Serial.print("Distanta : ");
  Serial.print(distance);
  Serial.println(" cm");
  delay(200);
  if (distance<20 and distance>0)
  {
    if (stare_releu == 0) 
    {
      stare_releu = 1;  
      digitalWrite(PIN_RELEU_1, HIGH); 
      goto fine;
    }
    else
    {
      stare_releu = 0;
      digitalWrite(PIN_RELEU_1, LOW);
    }
    fine: 
    Serial.println(" ");    
  } 
}
