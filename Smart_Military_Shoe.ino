#include <Servo.h>
#include <Wire.h>
#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
#include <SoftwareSerial.h>
#include <SoftwareSerial.h>
#include <TinyGPS.h>
#include <TinyGPS++.h>

#define REPORTING_PERIOD_MS 750
#define GPS_BAUD 9600
#define SIM800_BAUD 9600


SoftwareSerial sim800l(12, 13);
SoftwareSerial mySerial(10, 11);
TinyGPS gps;
PulseOximeter pox;
uint32_t tsLastReport = 0;
SoftwareSerial gpsSerial(10, 11);
SoftwareSerial sim800Serial(12, 13);
TinyGPSPlus gps1;
Servo s1, s2, s3;
int soil;
int moist;
int pos = 0 const int waterSensorPin = A1;
const int buzzerPin = 8;
int buttonPin = 9;
int buttonState;
Servo gate;

void setup() {
  Serial.begin(9600);
  s1.attach(2);
  s2.attach(3);
  s3.attach(4);
  s1.write(0);
  s2.write(0);
  s3.write(0);
  pinMode(buzzerPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  digitalWrite(buttonPin, HIGH);
  gate.attach(5);
  gate.write(0);
  Serial.begin(9600);
  sim800l.begin(9600);
  mySerial.begin(9600);
  Serial.begin(9600);
  delay(3000);
  Serial.print("Initializing pulse oximeter..");
  if (!pox.begin()) {
    Serial.println("FAILED");
    for (;;)
      ;
  } else {
    Serial.println("SUCCESS");
  }
  pox.setIRLedCurrent(MAX30100_LED_CURR_50MA);
  gpsSerial.begin(GPS_BAUD);
  sim800Serial.begin(SIM800_BAUD);
  sim800Serial.println("AT+CMGF=1");
  delay(100);
  sim800Serial.println("AT+CNMI=2,2,0,0,0");
  delay(100);
}


void loop() {
  soil = analogRead(A0);
  moist = map(soil, 0, 1023, 100, 0);
  if (moist > 50) {
    s1.write(90);
    delay(2);
    s2.write(90);
    delay(2);
    s3.write(90);
  } else {
    s1.write(0);
    delay(2);
    s2.write(0);
    delay(2);
    s3.write(0);
  }
  int sensorValue = analogRead(waterSensorPin);
  if (sensorValue > 570) {
    int outputValue = map(sensorValue,
                          570, 800, 0, 255);
    Serial.println(outputValue);
    digitalWrite(buzzerPin, HIGH);
  } else {
    digitalWrite(buzzerPin, LOW);
    buttonState = digitalRead(buttonPin);
    if (buttonState == 0) {
      gate.write(90);
      // delay(2000);
      // gate.write(0);
    } else {
      gate.write(0);
    }
  }
  pox.update();
  if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
    Serial.print("Heart rate:");
    Serial.print(pox.getHeartRate());
    Serial.print("bpm / SpO2:");
    Serial.print(pox.getSpO2());
    Serial.println("%");
    int heartRate = pox.getHeartRate();
    if (heartRate > 130) {
      bool newdata = false;
      unsigned long start = millis();
      // Every 5 seconds we print an update
      while (millis() - start < 5000) {
        if (mySerial.available()) {
          char c = mySerial.read();
          //Serial.print(c);
          if (gps.encode(c)) {
            newdata = true;
            break;
          }
        }
      }
      if (newdata) {
        gpsdump(gps);
        Serial.println();
      }
    }
    tsLastReport = millis();
  }
  if (sim800Serial.available()) {
    String sms = sim800Serial.readStringUntil();
    if (sms.indexOf("location") != -1) {
      sendLocationSMS();
    }
  }
  while (gpsSerial.available()) {
    if (gps1.encode(gpsSerial.read())) {
      sendLocationSMS();
    }
  }
}


void gpsdump(TinyGPS &gps) {
  long lat, lon;
  float flat, flon;
  unsigned long age;
  gps.f_get_position(&flat, &flon, &age);
  Serial.println("Sending SMS...");
  sim800l.print("AT+CMGF=1\r");
  delay(100);
  sim800l.print("AT+CMGS=
\"+8801704054900\"\r");
  delay(500);
sim800l.print("http://maps.google.
com/maps?q=loc:");
sim800l.print(flat == TinyGPS::
GPS_INVALID_F_ANGLE? 0.0 : flat, 6);
sim800l.print(",");
sim800l.print(flon == TinyGPS::
GPS_INVALID_F_ANGLE? 0.0 : flon, 6);
sim800l.print((char)26);
delay(500); sim800l.println();
Serial.println("Text Sent.");
delay(5000);

double rounding = 0.50;
for (uint8_t i = 0; i < digits; ++i)
  rounding /= 10.00;
number += rounding;
unsigned long int_part =
  (unsigned long)number;
double remainder = number
                   - (double)int_part;
Serial.print(int_part);
if (digits > 00) {
    Serial.print(".");
    while (digits-- > 0) {
      remainder *= 10.00;
      int toPrint = int(remainder);
      Serial.print(toPrint);
      remainder -= toPrint;
    }
}
}

void sendLocationSMS() {
  sim800Serial.println("AT+CMGF=1");
  sim800Serial.println("AT+CMGS=
\"+8801747904424\"");
  delay(100);
  sim800Serial.print("Latitude: ");
  sim800Serial.println(gps1.location.lat(), 6);
  delay(100);
  sim800Serial.print("Longitude: ");
  sim800Serial.println(gps1.location.lng(), 6);
  delay(100);
  sim800Serial.write((char)26);
  delay(1000);
}
