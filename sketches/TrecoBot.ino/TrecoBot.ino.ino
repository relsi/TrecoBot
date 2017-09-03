/*
 A primo.io fork using ESP8266 to control by Relsi Maron
 
*/

#include <ESP8266WiFi.h>            
#include <ESP8266WebServer.h>

//wifi credential
const char* ssid = "";
const char* password = "";

ESP8266WebServer server(80);

#define PWMA 5 //pin D1
#define PWMB 4 //pin D2
#define DIRA 0 //pin D3
#define DIRB 2 //pin D4

#define LED 16 //pin D0 LED bultin (just for debug)

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(DIRA, OUTPUT);
  pinMode(DIRB, OUTPUT);
  
  //Connect to the WiFi network
  WiFi.begin(ssid, password); 
  
  //Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    digitalWrite(LED, HIGH);
  }

  //just a joke
  server.on("/", public_html);
  //handle for the TrecoBot directions
  server.on("/move", move_bot);
  //start the esp8266 webserver
  server.begin();
  
}

void public_html() {
  server.send(200, "text/plain", "not for you here ;)");
}

void move_bot() {
    if(server.arg(0) == "1"){
       forward();
       delay(500);
       server.send(200);
    }else if(server.arg(0) == "2"){
      right();
      delay(500);
      server.send(200);
    }else if(server.arg(0) == "3"){
      left();
      delay(500);
      server.send(200);
    }else{
      server.send(403);
    }
}

void forward(){
  //turn on motorA and motorB
  digitalWrite(DIRA, LOW);
  digitalWrite(DIRB, LOW);  
  analogWrite(PWMA, 500);
  analogWrite(PWMB, 500);
  
  delay(500);
  
  //turn off motorA and motorB
  analogWrite(PWMA, 0);
  analogWrite(PWMB, 0);
}

void left(){
  //turn on motorB
  digitalWrite(DIRA, HIGH);
  digitalWrite(DIRB, LOW);
  
  analogWrite(PWMB, 500);
  
  delay(500);
  
  //turn off motorB
  analogWrite(PWMB, 0);
}

void right(){
  //turn on motorA
  digitalWrite(DIRA, LOW);
  digitalWrite(DIRB, HIGH);
  analogWrite(PWMA, 500);
  
  delay(500);
  
  //turn off motorA
  analogWrite(PWMA, 0);
}


void loop() {
  server.handleClient();

//  forward(); 
//  delay(1000);
//  left();
//  delay(500);
//  right();
//  delay(500);
}

