const int trigPin = 8;//ULTRA
const int echoPin = 10;
const int buzzer = 9;
long duration;
int distance;
int LDRPin = A1; //LDR
int lightintensity ;    
int waterPin = A0;//WATER
int moisture;
int percentage;
int map_low = 800;
int map_high = 400;
        
void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer,LOW);
  pinMode(2, OUTPUT);
 
}
void ultrasonic()
{
  Serial.print(distance); 
  Serial.println(" Object Alert");
  digitalWrite(buzzer,HIGH);
  for (int i=distance; i>0; i--)
    delay(10);
  digitalWrite(buzzer,LOW);
  for (int i=distance; i>0; i--)
    delay(10);
}
void checkdistance()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);    
  distance= duration*0.034/2;
}
void LDR()
{
  if(lightintensity < 30) 
      digitalWrite(2,HIGH);
    else 
      digitalWrite(2,LOW); 
    //delay(5); 
}
void watersensor()
{
  if (percentage>80){
      Serial.println("buzzing");
        //tone(buzzer, 1000); // Send 1KHz sound signal...
        //delay(100);        // ...for 1 sec
        //noTone(buzzer);     // Stop sound...
        //delay(100);        // ...for 1sec
    } 
}
void loop() {    
    checkdistance();
    lightintensity = analogRead(LDRPin);
    moisture = analogRead(waterPin);
    percentage = map(moisture , map_low, map_high , 0, 100);
    
    if (distance<50)
    {
       ultrasonic();  
    }  
    Serial.print("light intensity :"); 
    Serial.println(lightintensity);
    LDR();
    if(moisture<900)
    {
      Serial.print("Raw: ");
      Serial.println(moisture);
    }
    if(percentage<0)
    {
      percentage = 0;
      Serial.print("Percentage :");
      Serial.println(percentage); 
    }
    else
    {
      Serial.print("Percentage :");
      Serial.println(percentage); 
    }  
    watersensor();
    }
