/*
  SD card read/write

 This example shows how to read and write data to and from an SD card file
 The circuit:
 * SD card attached

 This example code is in the public domain.

 */
#include <Adafruit_LSM6DS33.h>

#include <Wire.h>
#include <Adafruit_LIS3MDL.h>
#include <Adafruit_Sensor.h>

Adafruit_LIS3MDL lis3mdl;
#define LIS3MDL_CLK 13
#define LIS3MDL_MISO 12
#define LIS3MDL_MOSI 11
#define LIS3MDL_CS 10

// For SPI mode, we need a CS pin
#define LSM_CS 10
// For software-SPI mode we need SCK/MOSI/MISO pins
#define LSM_SCK 13
#define LSM_MISO 12
#define LSM_MOSI 11
Adafruit_LSM6DS33 lsm6ds33;

#include <STM32SD.h>

// If SD card slot has no detect pin then define it as SD_DETECT_NONE
// to ignore it. One other option is to call 'SD.begin()' without parameter.
#ifndef SD_DETECT_PIN
#define SD_DETECT_PIN SD_DETECT_NONE
#endif

File myFile; //variable for SD card

const int hall_Sensor=A0; //hall sensor
int inputVal = 0; //hall sensor

const int buttonPin = 6;     // the number of the pushbutton pin
const int ledPin =  5;      // the number of the LED pin
int buttonState = 0;         // variable for reading the pushbutton status

// Define FSR pin:
#define fsrpin1 A1
#define fsrpin2 A2
//Define variable to store sensor readings:
int fsrreading1; //Variable to store FSR value
int fsrreading2;
unsigned long ms_since_start;

void setup()
{
  int counter = 0; //holds number of completed iterations
  
  pinMode(hall_Sensor,INPUT); //hall sensor

  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  
  // Open serial communications and wait for port to open:
 /* Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect.
  }
 */

if (! lis3mdl.begin_I2C()) {          // hardware I2C mode, can pass in address & alt Wire
  //if (! lis3mdl.begin_SPI(LIS3MDL_CS)) {  // hardware SPI mode
  //if (! lis3mdl.begin_SPI(LIS3MDL_CS, LIS3MDL_CLK, LIS3MDL_MISO, LIS3MDL_MOSI)) { // soft SPI
    //Serial.println("Failed to find LIS3MDL chip");
    while (1) { delay(10); }
  }
  if (!lsm6ds33.begin_I2C()) {
    // if (!lsm6ds33.begin_SPI(LSM_CS)) {
    // if (!lsm6ds33.begin_SPI(LSM_CS, LSM_SCK, LSM_MISO, LSM_MOSI)) {
    //Serial.println("Failed to find LSM6DS33 chip");
    while (1) {
      delay(10);
    }
  }
 
  lis3mdl.setPerformanceMode(LIS3MDL_MEDIUMMODE);
  //Serial.print("Performance mode set to: ");
  switch (lis3mdl.getPerformanceMode()) {
    case LIS3MDL_LOWPOWERMODE: break;
    case LIS3MDL_MEDIUMMODE: break;
    case LIS3MDL_HIGHMODE: break;
    case LIS3MDL_ULTRAHIGHMODE: break;
  }

  lis3mdl.setOperationMode(LIS3MDL_CONTINUOUSMODE);
  //Serial.print("Operation mode set to: ");
  // Single shot mode will complete conversion and go into power down
  switch (lis3mdl.getOperationMode()) {
    case LIS3MDL_CONTINUOUSMODE: break;
    case LIS3MDL_SINGLEMODE: break;
    case LIS3MDL_POWERDOWNMODE: break;
  }

  lis3mdl.setDataRate(LIS3MDL_DATARATE_155_HZ);
  // You can check the datarate by looking at the frequency of the DRDY pin
  //Serial.print("Data rate set to: ");
  switch (lis3mdl.getDataRate()) {
    case LIS3MDL_DATARATE_0_625_HZ: break;
    case LIS3MDL_DATARATE_1000_HZ: break;
  }
 

  lis3mdl.setIntThreshold(500);
  lis3mdl.configInterrupt(false, false, true, // enable z axis
                          true, // polarity
                          false, // don't latch
                          true); // enabled!

  lsm6ds33.setAccelDataRate(LSM6DS_RATE_12_5_HZ);
  //Serial.print("Accelerometer data rate set to: ");
  switch (lsm6ds33.getAccelDataRate()) {
  case LSM6DS_RATE_SHUTDOWN:
    //Serial.println("0 Hz");
    break;
  case LSM6DS_RATE_12_5_HZ:
    //Serial.println("12.5 Hz");
    break;
  case LSM6DS_RATE_6_66K_HZ:
    //Serial.println("6.66 KHz");
    break;
  }

  lsm6ds33.setGyroDataRate(LSM6DS_RATE_12_5_HZ);
  //Serial.print("Gyro data rate set to: ");
  switch (lsm6ds33.getGyroDataRate()) {
  case LSM6DS_RATE_SHUTDOWN:
    //Serial.println("0 Hz");
    break;
  case LSM6DS_RATE_12_5_HZ:
    //Serial.println("12.5 Hz");
    break;

  case LSM6DS_RATE_6_66K_HZ:
    //Serial.println("6.66 KHz");
    break;
  }

  lsm6ds33.configInt1(false, false, true); // accelerometer DRDY on INT1
  lsm6ds33.configInt2(false, true, false); // gyro DRDY on INT2



  //Serial.print("Initializing SD card...");
  while (!SD.begin(SD_DETECT_PIN))
  {
    delay(10);
  }
  //myFile.println("initialization done.");

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("test10.txt", FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    myFile.println("Writing to test10.txt...");

 

  while (counter < 20000) {

  sensors_event_t accel;
  sensors_event_t gyro;
  sensors_event_t temp;
  lsm6ds33.getEvent(&accel, &gyro, &temp);

  char tmp1[10]; dtostrf(accel.acceleration.x,1,2,tmp1); myFile.print(tmp1);
  myFile.print(","); char tmp2[10]; dtostrf(accel.acceleration.y,1,2,tmp2); myFile.print(tmp2);
  myFile.print(","); char tmp3[10]; dtostrf(accel.acceleration.z,1,2,tmp3); myFile.print(tmp3);

  myFile.print(","); char tmp4[10]; dtostrf(gyro.gyro.x,1,2,tmp4); myFile.print(tmp4);
  myFile.print(","); char tmp5[10]; dtostrf(gyro.gyro.y,1,2,tmp5); myFile.print(tmp5);
  myFile.print(","); char tmp6[10]; dtostrf(gyro.gyro.z,1,2,tmp6); myFile.print(tmp6);

    /* Or....get a new sensor event, normalized to uTesla */
  sensors_event_t event; 
  lis3mdl.getEvent(&event);
  /* Display the results (magnetic field is measured in uTesla) */
  myFile.print(","); char tmp7[10]; dtostrf(event.magnetic.x,1,2,tmp7); myFile.print(tmp7);
  myFile.print(","); char tmp8[10]; dtostrf(event.magnetic.y,1,2,tmp8); myFile.print(tmp8);
  myFile.print(","); char tmp9[10]; dtostrf(event.magnetic.z,1,2,tmp9); myFile.print(tmp9);
  

    // Read the FSR pin and store the output as fsrreading:
  fsrreading1 = analogRead(fsrpin1);
  fsrreading2 = analogRead(fsrpin2);
  
  // Print the fsrreading:
  myFile.print(","); char tmp10[10]; dtostrf(fsrreading1, 1,2, tmp10); myFile.print(tmp10);
  myFile.print(","); char tmp11[10]; dtostrf(fsrreading2, 1,2, tmp11); myFile.print(tmp11);

  myFile.print(",");

  inputVal = analogRead(hall_Sensor);
  if (inputVal < 1000)
    myFile.print("1");
  else
    myFile.print("0");

  ms_since_start = millis();
  myFile.print(","); char tmp12[10]; dtostrf(ms_since_start, 1,2, tmp12); myFile.print(tmp12);
  myFile.print(",");

  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // turn LED on:
    digitalWrite(ledPin, HIGH);
    myFile.println("1");
  } else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
    myFile.println("0");
  }
  
  counter = counter + 1;
  delayMicroseconds(10);
  }
  
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    //Serial.println("error opening test.txt");
  }
}

void loop()
{
  // nothing happens after setup
}
