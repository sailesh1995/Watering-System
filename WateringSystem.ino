/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  This example runs directly on ESP8266 chip.

  Note: This requires ESP8266 support package:
    https://github.com/esp8266/Arduino

  Please be sure to select the right ESP8266 module
  in the Tools -> Board menu!

  Change WiFi ssid, pass, and Blynk auth token to run :)
  Feel free to apply it to any other example. It's simple!
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "5a036c51adfa45a7b6924911d935793e";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Softwarica_Coventry";
char pass[] = "softwarica";

const int moistureAO = A0;
int AO = 0;       // Pin connected to A0 on the controller int
int tmp = 0;      // Value of the analog pin
int motor = 5; // Pin connected to the motor
BlynkTimer timer;

void setup()
{

  // Debug console
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  Serial.println("Soil moisture sensor");
  pinMode(moistureAO, INPUT);
  pinMode(motor, OUTPUT); // Set pin as output
  timer.setInterval(10000L, sendSensor);
  timer.setInterval(5000L, myTimerEvent);
}

void sendSensor(){
  float sensorData = analogRead(moistureAO);
  
  if(sensorData > 900){
    
    Blynk.notify("Your plant is dry. Please water your plants");
  
  }else{
    digitalWrite(motor, HIGH);
    }
}

void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  float sensorData = analogRead(moistureAO);
  Blynk.virtualWrite(V5, sensorData);
}

BLYNK_WRITE(V6){
  int i = param.asInt();
  if(i==1){
      digitalWrite(motor, HIGH);
    }else{
        digitalWrite(motor, LOW);
      }
  }

void loop()
{
  Blynk.run();
  timer.run();
  tmp = analogRead( moistureAO );  
if ( tmp != AO ) {    AO = tmp;    
Serial.print("A = "); // Show the resistance value of the sensor                           
// in the IDE   
Serial.println(AO);  
} 
delay (1000); 
 
}
