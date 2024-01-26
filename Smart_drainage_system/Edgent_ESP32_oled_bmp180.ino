
#define BLYNK_TEMPLATE_ID "Your Template id"
#define BLYNK_TEMPLATE_NAME "Your Template name"
#define BLYNK_FIRMWARE_VERSION        "0.1.0" //enter the version which you have

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG

// Uncomment your board, or configure a custom board in Settings.h
//#define USE_ESP32_DEV_MODULE
//#define USE_ESP32C3_DEV_MODULE
//#define USE_ESP32S2_DEV_KIT
//#define USE_WROVER_BOARD
//#define USE_TTGO_T7
//#define USE_TTGO_T_OI

#include "BlynkEdgent.h"
#include <Adafruit_BMP085.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>


#define i2c_Address 0x3c
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1 

Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2


#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 

Adafruit_BMP085 bmp;
  
const int analogInPin = 34;
int sensorValue = 0;
int buttonState = 0;

const int buttonPin = 5;

int ServoPin1 = 18;
int ServoPin2 = 19;

const unsigned long eventInterval = 2000;
unsigned long previousTime = 0;

void setup()
{
  Serial.begin(115200);
  BlynkEdgent.begin();
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ServoPin1,OUTPUT);
  pinMode(ServoPin2,OUTPUT);
  
  display.begin(i2c_Address, true);

  if (!bmp.begin()) {
	Serial.println("Could not find a valid BMP085 sensor, check wiring!");
	while (1) {}
  }

}

void loop() {
   display.clearDisplay();

    Serial.print("Temperature = ");
    Serial.print(bmp.readTemperature());
    double t = bmp.readTemperature();
    Serial.println(" *C");
   
    display.setTextSize(1);
    display.setTextColor(SH110X_WHITE);
    display.setCursor(0,0);
    display.println("Temperature = ");
    display.setCursor(90,0);
    display.println(bmp.readTemperature());
    Blynk.virtualWrite(V0, t);


    Serial.print("Pressure = ");
    Serial.print(bmp.readPressure());
    Serial.println(" Pa");
    int p = bmp.readPressure();

    display.setTextSize(1);
    display.setTextColor(SH110X_WHITE);
    display.setCursor(0,15);
    display.println("Pressure = ");
    display.setCursor(80,15);
    display.println(bmp.readPressure());
    Blynk.virtualWrite(V1, p);
    

    Serial.print("Altitude = ");
    Serial.print(bmp.readAltitude());
    Serial.println(" meters");
    double a = bmp.readAltitude();

    display.setTextSize(1);
    display.setTextColor(SH110X_WHITE);
    display.setCursor(0,30);
    display.println("Altitude = ");
    display.setCursor(80,30);
    display.println(bmp.readAltitude());
    Blynk.virtualWrite(V2, a);


    sensorValue = analogRead(analogInPin);
    Serial.print("sensor = ");
    Serial.println(sensorValue);
    double w = sensorValue;

    display.setTextSize(1);
    display.setTextColor(SH110X_WHITE);
    display.setCursor(0,43);
    display.println("water level = ");
    display.setCursor(80,43);
    display.println(sensorValue);
    Blynk.virtualWrite(V3,w);


    // Serial.print("Pressure at sealevel (calculated) = ");
    // Serial.print(bmp.readSealevelPressure());
    // Serial.println(" Pa");



    // Serial.print("Real altitude = ");
    // Serial.print(bmp.readAltitude(101500));
    // Serial.println(" meters");

    // display.setTextSize(1);
    // display.setTextColor(SH110X_WHITE);
    // display.setCursor(0,43);
    // display.println("Real altitude = ");
    // display.setCursor(90,43);
    // display.println(bmp.readAltitude(101500));

     unsigned long currentTime = millis();

    buttonState = digitalRead(buttonPin);

  if (buttonState == LOW || sensorValue >= 2000) {

        if (currentTime - previousTime >= eventInterval) {

            digitalWrite(ServoPin1,HIGH);
            digitalWrite(ServoPin2,HIGH);
            
            
          
            previousTime = currentTime;
  }
            display.setTextSize(1);
            display.setTextColor(SH110X_WHITE);
            display.setCursor(0,55);
            display.println("servo in position");

    
  } else {
        digitalWrite(ServoPin1,LOW);
        digitalWrite(ServoPin2,LOW);
        display.setTextSize(1);
        display.setTextColor(SH110X_WHITE);
        display.setCursor(0,55);
        display.println("servo idle");

    }



    display.display();
    

  BlynkEdgent.run();
  delay(300);
}

