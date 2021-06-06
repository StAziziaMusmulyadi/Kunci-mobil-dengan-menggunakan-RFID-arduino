#include <Servo.h>
#include <SPI.h>
#include <RFID.h>
#define SS_PIN 10
#define RST_PIN 9
const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution
int stepCount = 0;

Servo myservo;
int LED1 = 6;
int LED2 = 7;
int Status1 = 0;
int pos = 0;
int servo_speed = 30;

RFID rfid(SS_PIN, RST_PIN);
String rfidCard;

void setup() {
  Serial.begin(9600);
  Serial.println("Starting the RFID Reader...");
  SPI.begin();
  rfid.init();
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  myservo.attach(5);  // attaches the servo on pin 9 to the servo object
  myservo.write(0);
}

void loop() {
  if (rfid.isCard()) {
    if (rfid.readCardSerial()) {
      rfidCard = String(rfid.serNum[0]) + " " + String(rfid.serNum[1]) + " " + String(rfid.serNum[2]) + " " + String(rfid.serNum[3]);
      Serial.println(rfidCard);
      if (rfidCard == "71 36 4 217") {
        myservo.write (100);
        digitalWrite(6, HIGH);
        digitalWrite(7, LOW);
      }
    }
  }
  else {
    myservo.write (0);
    digitalWrite(6, LOW);
    digitalWrite(7, HIGH);
  }

  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}
