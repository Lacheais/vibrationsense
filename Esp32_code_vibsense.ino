#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_ADXL345_U.h"
#include "WiFi.h"
#include "ThingSpeak.h"
#include "Header.h"

WiFiClient client;

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

int counter = 0;
float accelx, accely, accelz;

void setup(void) 
{
  Serial.begin(SERIAL_BAUD);
  wifisetup();
  Serial.println("Accelerometer Test"); Serial.println("");

  if(!accel.begin())
  {
    Serial.println("Ooops, no ADXL345 detected... Check your wiring!");
    while(1);
  }
  accel.setRange(ADXL345_RANGE_16_G);
  
  displaySensorDetails();
  displayDataRate();
  displayRange();
  Serial.println("");

  pinMode(LED_PIN, OUTPUT);
}

void loop(void) 
{
  sensors_event_t event; 
  accel.getEvent(&event);
 
  accelx = event.acceleration.x / G_ACCEL;
  accely = event.acceleration.y / G_ACCEL;
  accelz = event.acceleration.z / G_ACCEL;
  Serial.print("X: "); Serial.println(accelx); 
  Serial.print("Y: "); Serial.println(accely); 
  Serial.print("Z: "); Serial.println(accelz); 
  DEL_1;

  if (P_WAVE){
      counter++;
      Serial.println(counter);
      DEL_1;
  }else {
    counter--;
    if (counter < 0){
      counter = 0;
    }
    Serial.println(counter);
  }

  if (counter >= 2){
    if (WEAK_EQ){
      digitalWrite(LED_PIN, HIGH);
      DEL_0_1;
      Serial.println("Possible Earthquake");
      Serial.println(" ");
    }
    if (MID_EQ){
      digitalWrite(LED_PIN, HIGH);
      Serial.println("May lindol guys");
      tone(BUZZ_PIN, BUZZ_TONE_1, BUZZ_DURATION_0_5);
      DEL_0_1;
    }
    else if (STRONG_EQ){
      Serial.println("MAMATAY TAYO GUYS!");
      digitalWrite(12, HIGH);
      tone(BUZZ_PIN, BUZZ_TONE_2, BUZZ_DURATION_1_5);
      DEL_1;
    }
  }
  else{
    digitalWrite(LED_PIN, LOW);
  }
  wifiloop();
}

void wifisetup() {
  connectToWIFI();
  ThingSpeak.begin(client);
}

void wifiloop() {
  ThingSpeak.setField(SUCAT_X, accelx);
  ThingSpeak.setField(SUCAT_Z, accelz);
  ThingSpeak.writeFields(CHANNEL_ID, CHANNEL_API_KEY);
  DEL_15;
}

void connectToWIFI(){
  Serial.print("Connecting to WiFi");
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_NAME, WIFI_PASS);

  unsigned long startAttemptTime = millis();
  while(WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < WIFI_TIMEOUT){
    Serial.print(".");
    DEL_0_1;
  }

  if (WiFi.status() != WL_CONNECTED){
    Serial.print("Failed to Connect!");
    DEL_1;
  }else{
    Serial.print("Connected!");
    Serial.print(WiFi.localIP());
    DEL_1;
  }
}

void displaySensorDetails(void)
{
  sensor_t sensor;
  accel.getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" m/s^2");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" m/s^2");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" m/s^2"); 
  Serial.println("------------------------------------");
  Serial.println("");
  DEL_1_5;
}

void displayDataRate(void)
{
  Serial.print  ("Data Rate:    "); 
 
  switch(accel.getDataRate())
  {
    case ADXL345_DATARATE_3200_HZ:
      Serial.print  ("3200 "); 
      break;
    case ADXL345_DATARATE_1600_HZ:
      Serial.print  ("1600 "); 
      break;
    case ADXL345_DATARATE_800_HZ:
      Serial.print  ("800 "); 
      break;
    case ADXL345_DATARATE_400_HZ:
      Serial.print  ("400 "); 
      break;
    case ADXL345_DATARATE_200_HZ:
      Serial.print  ("200 "); 
      break;
    case ADXL345_DATARATE_100_HZ:
      Serial.print  ("100 "); 
      break;
    case ADXL345_DATARATE_50_HZ:
      Serial.print  ("50 "); 
      break;
    case ADXL345_DATARATE_25_HZ:
      Serial.print  ("25 "); 
      break;
    case ADXL345_DATARATE_12_5_HZ:
      Serial.print  ("12.5 "); 
      break;
    case ADXL345_DATARATE_6_25HZ:
      Serial.print  ("6.25 "); 
      break;
    case ADXL345_DATARATE_3_13_HZ:
      Serial.print  ("3.13 "); 
      break;
    case ADXL345_DATARATE_1_56_HZ:
      Serial.print  ("1.56 "); 
      break;
    case ADXL345_DATARATE_0_78_HZ:
      Serial.print  ("0.78 "); 
      break;
    case ADXL345_DATARATE_0_39_HZ:
      Serial.print  ("0.39 "); 
      break;
    case ADXL345_DATARATE_0_20_HZ:
      Serial.print  ("0.20 "); 
      break;
    case ADXL345_DATARATE_0_10_HZ:
      Serial.print  ("0.10 "); 
      break;
    default:
      Serial.print  ("???? "); 
      break;
  } 
  Serial.println(" Hz"); 
}

void displayRange(void)
{
  Serial.print ("Range:         +/- ");
 
  switch(accel.getRange())
  {
    case ADXL345_RANGE_16_G:
      Serial.print  ("16 "); 
      break;
    case ADXL345_RANGE_8_G:
      Serial.print  ("8 "); 
      break;
    case ADXL345_RANGE_4_G:
      Serial.print  ("4 "); 
      break;
    case ADXL345_RANGE_2_G:
      Serial.print  ("2 "); 
      break;
    default:
      Serial.print  ("?? "); 
      break;
  } 
  Serial.println(" g"); 
}


