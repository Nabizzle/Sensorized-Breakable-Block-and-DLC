# Sensorized-Breakable-Block-and-DLC
A repository of code for the sensorized, magnetic, breakable block and Deep Lab Cut tracking of the block.

# Table of Contents

* [Test Summary](#test-summary)
* [Getting Started](#getting-started)
  * [Prerequisites](#prerequisites)
    * [Featherboard Setup](#featherboard-setup)
      * [Board Setup on Arduino IDE](#board-setup-on-arduino-ide)
      * [Library Setup on Arduino IDE](#library-setup-on-arduino-ide)
      * [Obtaining Scripts from GitHub](#obtaining-scripts-from-github)
      * [Uploading to the Featherboard](#uploading-to-the-featherboard)
    * [Installing DLC on Windows](#installing-dlc-on-windows)
      * [Install Anaconda and Python](#install-anaconda-and-python)
      * [Download DLC](#download-dlc)
      * [Install DeepLabCut](#install-deeplabcut)
  * [Breakable Block Set-up](#breakable-block-set-up)
    * [Breakable Block Circuit](#breakable-block-circuit)
    * [Soldering Instructions](#soldering-instructions)
    * [Charging the Block](#charging-the-block)
    * [Connecting the Block](#connecting-the-block)
    * [Changing Block Strength](#changing-block-strength)
  * [Experimental Set-up](#experimental-set-up)
* [Running the Tests](#running-the-tests)
  * [Test Procedure](#test-procedure)
  * [Data Collection](#data-collection)
    * [DLC Data](#dlc-data)
    * [Featherboard](#featherboard)
    * [EMG Recording](#emg-recording)
  * [Data Analysis](#data-analysis)
    * [DLC Analysis](#dlc-analysis)
      * [Opening DeepLabCut](#opening-deeplabcut)
      * [Analyzing a Video](#analyzing-a-video)
      * [Assessing Network Confidence](#assessing-network-confidence)
      * [Creating a Labeled Video](#creating-a-labeled-video)
      * [Improving the Network](#improving-the-network)
    * [Featherboard](#featherboard)
      * [Analysis of Breakable Box MicroSD Card Data with Matlab](#analysis-of-breakable-box-microsd-card-data-with-matlab)
    * [EMG Analysis](#emg-analysis)
    * [Combining the Data](#combining-the-data)
 * [Author](#author)
 * [Acknowledgments](#acknowledgments)
 * [Description of Scripts](#description-of-scripts)

# Test Summary
The purpose of this experiment is to track grip modulation during a breakable block test with a sensory enabled prosthesis. 
Data will be gathered from 3 major sources:
* A sensorized, magnetic breakable block with the following data streams:
  * an inertial measurement unit (IMU) to track
    * accelerations
    * rotations
    * magnetic fields
  * a hall effect sensor to track the moment the block breaks
  * two detachable force sensitive resistors (FSRs) to track the force on the block
* A markerless motion capture system, Deep Lab Cut (DLC) which takes in:
  * video footage
* Electromyographic data from the subject using a force controlled prothesis

# Getting Started
Follow the steps below to set up all parts of the test

## Prerequisites
### Featherboard Setup
The development board used in this experiment is the Adafruit STM32F405 Feather Express. Development boards act as microcomputers, allowing an individual to run basic computer scripts, collect measurements from attached sensors, and write/read data from an SD card without direct use of a computer.

<img src = "https://github.com/CaseFNI/Sensorized-Breakable-Block-and-DLC/blob/main/Docs/Images/Feather%20Board.png" width="300">

Begin by removing the included set of plain headers from the package containing the feather board. Individually break off two plain headers from the main strip of headers (shown below). Place the plain headers onto the breadboard, locating them. Solder the two headers into their respective pinout holes, ensuring that the connections are good joints for proper signal transmission.
To collect accelerometer, gyroscope, and magnetometer data, an Adafruit LSM6DS33 + LIS3MDL - 9 DoF IMU was employed. Remove the included Stemma QT connector and attach it to the I2C bus (as shown below).
Then, connect the remaining open end of the Stemma QT connector to the I2C bus on the Featherboard.

<img src = "https://github.com/CaseFNI/Sensorized-Breakable-Block-and-DLC/blob/main/Docs/Images/Feather%20Board%20with%20IMU.png" width="500">

Next, flip the featherboard over to reveal the microSD card slot. Obtain a microSD card with adequate storage for your needs (in this case, a 16GB SanDisk was used). Insert the microSD card into the slot, clicking the card into its secured position. To remove the card, gently push the card further into the slot, upon which a clicking sound should be heard, and the card should pop out far enough for you to remove it from the board.

<img src = "https://github.com/CaseFNI/Sensorized-Breakable-Block-and-DLC/blob/main/Docs/Images/SD%20Card%20Reader.png" width="300">

#### Board Setup on Arduino IDE
