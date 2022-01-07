/*
  SD card read/write

 This example shows how to read and write data to and from an SD card file
 The circuit:
 * SD card attached

 This example code is in the public domain.

 */
#include <Adafruit_LSM6DS33.h> //import the library for the IMU accelerometer and gyroscope

#include <Wire.h>
#include <Adafruit_LIS3MDL.h> //import the library for the IMU magnetometer
#include <Adafruit_Sensor.h> //import the general sensor library for Adafruit products

Adafruit_LIS3MDL lis3mdl; //assign the pins of the magnetometer
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

#include <STM32SD.h> //import the SD card library for STM32 development boards

// If SD card slot has no detect pin then define it as SD_DETECT_NONE
// to ignore it. One other option is to call 'SD.begin()' without parameter.
#ifndef SD_DETECT_PIN
#define SD_DETECT_PIN SD_DETECT_NONE
#endif

File myFile; //variable for SD card

const int hall_Sensor=A0; //analog pin for reading data from the hall sensor
int inputVal = 0; //

const int buttonPin = 6;     // the number of the pushbutton pin
const int ledPin =  5;      // the number of the LED pin
int buttonState = 0;         // variable for reading the pushbutton status

// Define FSR pin:
#define fsrpin1 A1 //define the analog pin for reading data from one of the force sensitive resistors
#define fsrpin2 A2 //define the analog pin for reading data from the other force sensitive resistor
//Define variable to store sensor readings:
int fsrreading1; //Variable to store FSR value
int fsrreading2;

unsigned long ms_since_start; //variable for holding the number of milliseconds since the code has started running

void setup()
{
  //Serial.begin(115200);
  int counter = 0; //holds number of completed iterations
  
  pinMode(hall_Sensor,INPUT); //initialize the hall sensor pin as an input

  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);


//The following two blocks of conditional statements perform error checking
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

//The user can increase the performance/power consumption of the magnetometer for higher data collection rates
  lis3mdl.setPerformanceMode(LIS3MDL_MEDIUMMODE); //to 
  //Serial.print("Performance mode set to: ");
  switch (lis3mdl.getPerformanceMode()) {
    case LIS3MDL_LOWPOWERMODE: break;
    case LIS3MDL_MEDIUMMODE: break;
    case LIS3MDL_HIGHMODE: break;
    case LIS3MDL_ULTRAHIGHMODE: break;
  }
  
//Set the magnetometer collect data continously
  lis3mdl.setOperationMode(LIS3MDL_CONTINUOUSMODE);
  //Serial.print("Operation mode set to: ");
  // Single shot mode will complete conversion and go into power down
  switch (lis3mdl.getOperationMode()) {
    case LIS3MDL_CONTINUOUSMODE: break;
    case LIS3MDL_SINGLEMODE: break;
    case LIS3MDL_POWERDOWNMODE: break;
  }

//The user can change the rate at which the magnetometer outputs data
  lis3mdl.setDataRate(LIS3MDL_DATARATE_155_HZ); //to increase the rate of data collection, format the argument passed as LIS3MDL_DATARATE_insertDataRate_HZ (decimal places, as in 12.5, are denoted with an underscore)
  // You can check the datarate by looking at the frequency of the DRDY pin
  //Serial.print("Data rate set to: ");
  switch (lis3mdl.getDataRate()) {
    case LIS3MDL_DATARATE_0_625_HZ: break;
    case LIS3MDL_DATARATE_1000_HZ: break;
  }

 //Configure the magnetometer
  lis3mdl.setIntThreshold(500);
  lis3mdl.configInterrupt(false, false, true, // enable z axis
                          true, // polarity
                          false, // don't latch
                          true); // enabled!

//The user can change the rate at which the accelerometer outputs data
  lsm6ds33.setAccelDataRate(LSM6DS_RATE_12_5_HZ); //to increase the rate of data collection, format the argument of the function as LSM6DS_RATE_insertDataRate_HZ
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

//The user can change the rate at which the gyroscope outputs data
  lsm6ds33.setGyroDataRate(LSM6DS_RATE_12_5_HZ); //to increase the rate of data collection, format the argument of the function as LSM6DS_RATE_insertDataRate_HZ
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

  //Configure the accelerometer and gyroscope
  lsm6ds33.configInt1(false, false, true); // accelerometer DRDY on INT1
  lsm6ds33.configInt2(false, true, false); // gyro DRDY on INT2



  //Serial.print("Initializing SD card...");

  //Ensure that the SD card is detected by the development board
  while (!SD.begin(SD_DETECT_PIN))
  {
    delay(10);
  }
  //myFile.println("initialization done.");

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  int fileCounter = 0;
  //String fileName = "test0.txt";
  const char *fileName_conv;
  String fileName = "test"+String(fileCounter)+".txt";
  fileName_conv = fileName.c_str();
  
  while (SD.exists(fileName_conv)) {
    fileCounter += 1;
    fileName = "test"+String(fileCounter)+".txt";
    fileName_conv = fileName.c_str();
  }

  delay(5000);
  
  myFile = SD.open(fileName_conv, FILE_WRITE); //write to the .txt file with the name "test"

  myFile.println("Writing a new dataset ..."); //indicates in the written text of the file that a new trial of data collection has begun

  while (counter < 2000) { //The user can change the number of data points that are collected during a trial by changing the number x, where counter < x, in the while loop's conditional statement

//The following four lines reset the IMU's accelerometer and gyroscope in order to permit their collection of a new data point
  sensors_event_t accel;
  sensors_event_t gyro;
  sensors_event_t temp;
  lsm6ds33.getEvent(&accel, &gyro, &temp);

//Print the accelerometer readings in x,y,z
  char tmp1[10]; dtostrf(accel.acceleration.x,1,2,tmp1); myFile.print(tmp1);
  myFile.print(","); char tmp2[10]; dtostrf(accel.acceleration.y,1,2,tmp2); myFile.print(tmp2);
  myFile.print(","); char tmp3[10]; dtostrf(accel.acceleration.z,1,2,tmp3); myFile.print(tmp3);

//Print the gyroscope readings in x,y,z
  myFile.print(","); char tmp4[10]; dtostrf(gyro.gyro.x,1,2,tmp4); myFile.print(tmp4);
  myFile.print(","); char tmp5[10]; dtostrf(gyro.gyro.y,1,2,tmp5); myFile.print(tmp5);
  myFile.print(","); char tmp6[10]; dtostrf(gyro.gyro.z,1,2,tmp6); myFile.print(tmp6);

//The following two lines reset the IMU's magnetometer in order to permit its collection of a new data point
  sensors_event_t event; 
  lis3mdl.getEvent(&event);
  /* Display the results (magnetic field is measured in uTesla) */
  myFile.print(","); char tmp7[10]; dtostrf(event.magnetic.x,1,2,tmp7); myFile.print(tmp7);
  myFile.print(","); char tmp8[10]; dtostrf(event.magnetic.y,1,2,tmp8); myFile.print(tmp8);
  myFile.print(","); char tmp9[10]; dtostrf(event.magnetic.z,1,2,tmp9); myFile.print(tmp9);
  

  // Read the FSR pin and store the output as fsrreading1 and fsrreading2:
  fsrreading1 = analogRead(fsrpin1);
  fsrreading2 = analogRead(fsrpin2);
  
  // Print the fsrreadings on the text file of the SD car:
  myFile.print(","); char tmp10[10]; dtostrf(fsrreading1, 1,2, tmp10); myFile.print(tmp10);
  myFile.print(","); char tmp11[10]; dtostrf(fsrreading2, 1,2, tmp11); myFile.print(tmp11);
  //Serial.print(tmp10);
  //Serial.print(",");
  //Serial.println(tmp11);
  myFile.print(",");

//Read the value of the hall sensor pin and output whether a magnet passed by ("1") or no magnet has passed by the sensor ("0")
  inputVal = analogRead(hall_Sensor);

  //Print the readings on the text file of the SD card
  if (inputVal < 1000)
    myFile.print("1");
  else
    myFile.print("0");

//Mark the number of milliseconds that have elapsed since the code started running
  ms_since_start = millis();
  myFile.print(","); char tmp12[10]; dtostrf(ms_since_start, 1,2, tmp12); myFile.print(tmp12);
  myFile.print(",");

//Read whether the button has been switched to HIGH ("1") or LOW ("0"), denoting the period during which a trial has occurred ("1" present)
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // turn LED on:
    digitalWrite(ledPin, HIGH);
    myFile.println("1"); //print the button's state on the text file of the SD card
  } else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
    myFile.println("0"); //print the button's state on the text file of the SD card
  }
  
  counter = counter + 1; //increment the variable storing the number of iterations that have occurred
  delayMicroseconds(10);
  }
  digitalWrite(ledPin, LOW);
  
    // close the file:
    myFile.close();
    delay(2000);
}

void loop()
{
  //fancy LED sequence to indicate end of trial
  digitalWrite(ledPin, HIGH);
  delay(500);
  digitalWrite(ledPin, LOW);
  delay(500);
}
