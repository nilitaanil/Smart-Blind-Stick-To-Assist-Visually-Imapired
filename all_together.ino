#include <SoftwareSerial.h>
SoftwareSerial mySerial(11, 12);
const int inPin = 7;
const int trigPin = 8;//ULTRA
const int echoPin = 10;
const int buzzer = 9;
const int pothole_trig = 5;
const int pothole_echo = 6;
long duration;
long pothole_duration;
int distance;
int pothole_distance;
int LDRPin = A1; //LDR
int lightintensity ;    
int waterPin = A0;//WATER
int moisture;
int percentage;
int map_low = 800;
int map_high = 400;
        
void setup() {
  mySerial.begin(9600);
  Serial.begin(9600);
  delay(100);
  pinMode(inPin, INPUT);
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  pinMode(pothole_trig, OUTPUT);
  pinMode(pothole_echo, INPUT);
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer,LOW);
  pinMode(2, OUTPUT);
 
}
void ultrasonic()
{
  Serial.print(distance); 
  Serial.println(" pothole Alert");
  digitalWrite(buzzer,HIGH);
  for (int i=distance; i>0; i--)
    delay(10);
  digitalWrite(buzzer,LOW);
  for (int i=distance; i>0; i--)
    delay(10);
}
void pothole_ultrasonic()
{
  Serial.print(pothole_distance); 
  Serial.println(" Object Alert");
  digitalWrite(buzzer,HIGH);
  for (int i=pothole_distance; i>0; i--)
    delay(10);
  digitalWrite(buzzer,LOW);
  for (int i=pothole_distance; i>0; i--)
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
void checkpothole()
{
  digitalWrite(pothole_trig, LOW);
  delayMicroseconds(2);
  digitalWrite(pothole_trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(pothole_trig, LOW);
  pothole_duration = pulseIn(pothole_echo, HIGH);    
  pothole_distance= pothole_duration*0.034/2;
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
      //Serial.println("buzzing");
      tone(buzzer, 1000); // Send 1KHz sound signal...
      delay(100);        // ...for 1 sec
      noTone(buzzer);     // Stop sound...
      delay(100);        // ...for 1sec
    } 
}
void SendMessage()
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+919008791799\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.println("There is an emergency !!");// The SMS text you want to send
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}

void loop() {    
    
    
    lightintensity = analogRead(LDRPin);
    moisture = analogRead(waterPin);
    percentage = map(moisture , map_low, map_high , 0, 100);
    checkdistance();
    if (distance<50)
    {
       ultrasonic();  
    }  
    checkpothole();
    if (pothole_distance<50)
    {
       pothole_ultrasonic();  
    }
    //Serial.print("light intensity :"); 
    //Serial.println(lightintensity);
    LDR();
    watersensor();

   int val = digitalRead(inPin);  // read input value
     if (val == LOW) {      
    //digitalWrite(ledPin, LOW); 
    SendMessage();
    
     } 
    
}
