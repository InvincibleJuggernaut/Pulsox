#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Blynk.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#include "MAX30105.h"
#include "heartRate.h"
#include "spo2_algorithm.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);
MAX30105 sensor;

char auth[] = "";             
char ssid[] = "";                                     
char pass[] = "";

const byte RATE_SIZE = 4; 
byte rates[RATE_SIZE];
byte rateSpot = 0;
long lastBeat = 0; 

float beatsPerMinute;
int beatAvg;

double aveRed = 0;
double aveIr = 0;
double sumIrRMS; 
double sumRedRMS;
double fRate = 0.95;
double SpO2 = 0;

void setup()
{
  Serial.begin(115200);

  Blynk.begin(auth, ssid, pass);
  
  if (!sensor.begin(Wire, I2C_SPEED_FAST)) 
  {
    Serial.println("MAX30102 not found");
    while (1);
  }
  
  sensor.setup(); 
  sensor.setPulseAmplitudeRed(0x0A); 
  sensor.setPulseAmplitudeGreen(0); 

  lcd.init();
  lcd.backlight();
}

void loop()
{
  Blynk.run();
    
  long irValue = sensor.getIR();
  long red = sensor.getRed();

  sumRedRMS = 0.0; 
  sumIrRMS = 0.0;
     
  if (checkForBeat(irValue) == true)
  {
    long ir = irValue;
    double fred = (double)red;
    double fir = (double)ir;
    aveRed = aveRed * fRate + (double)red * (1.0 - fRate);
    aveIr = aveIr * fRate + (double)ir * (1.0 - fRate);
    sumRedRMS += (fred - aveRed) * (fred - aveRed);
    sumIrRMS += (fir - aveIr) * (fir - aveIr);

    double R = (sqrt(sumRedRMS) / aveRed) / (sqrt(sumIrRMS) / aveIr);
    SpO2 = -23.3 * (R - 0.4) + 100;
    
    long delta = millis() - lastBeat;
    lastBeat = millis();

    beatsPerMinute = 60 / (delta / 1000.0);

    if (beatsPerMinute < 255 && beatsPerMinute > 20)
    {
      rates[rateSpot++] = (byte)beatsPerMinute;
      rateSpot %= RATE_SIZE;

      beatAvg = 0;
      for (byte x = 0 ; x < RATE_SIZE ; x++)
        beatAvg += rates[x];
      beatAvg /= RATE_SIZE;
    }

  Blynk.virtualWrite(V0, beatAvg);
  Blynk.virtualWrite(V1, int(SpO2+10));
  
  }
  
  if (irValue < 50000)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("     PULSOX     ");
    Blynk.virtualWrite(V0, 0);
    Blynk.virtualWrite(V1, 0);
    delay(2000);
  }

  lcd.setCursor(0,1);
  lcd.print("HBPM");
  lcd.setCursor(5,1);
  lcd.print(beatAvg);

  lcd.setCursor(9,1);
  lcd.print("SpO2");
  lcd.setCursor(14,1);
  lcd.print(int(SpO2+10));
  
}
