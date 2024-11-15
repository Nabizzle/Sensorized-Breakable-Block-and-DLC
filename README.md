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
    * [Featherboard Data](#featherboard-data)
    * [EMG Recording](#emg-recording)
  * [Data Analysis](#data-analysis)
    * [DLC Analysis](#dlc-analysis)
      * [Opening DeepLabCut](#opening-deeplabcut)
      * [Analyzing a Video](#analyzing-a-video)
      * [Assessing Network Confidence](#assessing-network-confidence)
      * [Creating a Labeled Video](#creating-a-labeled-video)
      * [Improving the Network](#improving-the-network)
      * [Creating Calibrated Plots](#creating-calibrated-plots)
      * [Transferring Your Network](#transferring-your-network)
    * [Featherboard](#featherboard)
      * [Analysis of Breakable Box MicroSD Card Data with Matlab](#analysis-of-breakable-box-microsd-card-data-with-matlab)
    * [EMG Analysis](#emg-analysis)
    * [Combining the Data](#combining-the-data)
 * [Authors](#authors)
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
### Materials for the Breakable Block
Development Board (1): https://www.adafruit.com/product/4382

9-DoF Inertial Measurement Unit (1): https://www.adafruit.com/product/4485

Stemma QT Connector (1): https://www.adafruit.com/product/4399

Hall Sensor (1): https://www.adafruit.com/product/158

MicroSD Card (1): https://www.amazon.com/SanDisk-COMINU024966-16GB-microSD-Card/dp/B004KSMXVM/ref=asc_df_B004KSMXVM/?tag=hyprod-20&linkCode=df0&hvadid=309776868400&hvpos=&hvnetw=g&hvrand=15168076603432715634&hvpone=&hvptwo=&hvqmt=&hvdev=c&hvdvcmdl=&hvlocint=&hvlocphy=9015305&hvtargid=pla-568819849086&psc=1

Force-Sensitive Resistors (2): https://www.adafruit.com/product/166

Battery (1): https://www.adafruit.com/product/3898

Female Headers (1 set): https://www.adafruit.com/product/2886

Heatshrink Tubing (1 set): https://www.adafruit.com/product/1649

2-Pin JST Cables (4): https://www.adafruit.com/product/261#tutorials

2-Pin JST Connectors (4): https://www.adafruit.com/product/1769#tutorials

3-Pin JST Cables (1): https://www.adafruit.com/product/4336#tutorials

3-Pin JST Connectors (1): https://www.adafruit.com/product/4391#tutorials

1 kOhm Resistor (3): https://www.adafruit.com/product/4294

330 kOhm Resistor (2): https://www.mouser.com/ProductDetail/Vishay-Beyschlag/MBB02070C2209FCT00?qs=PwR17mNzlcNasAfQWVUeXQ%3D%3D&mgh=1&gclid=CjwKCAjwjdOIBhA_EiwAHz8xm3erHz4jhEKvgGDCFvZZRFm7vF4IB3KdpdJlSs9pUisXKtLMqwhEHRoC8cAQAvD_BwE

Switch (1): https://www.sparkfun.com/products/9609

LED (1): https://www.adafruit.com/product/297

Heat Set Inserts (1 package): https://www.mcmaster.com/94459A110/

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
Visit the Arduino [website](https://www.arduino.cc/en/software) to download the Arduino IDE that best matches your computer’s specifications.

Navigate to **File** > **Preferences** in the top dropdown menus, and to the right of Additional Boards Manager URLs, copy and paste:
`https://github.com/stm32duino/BoardManagerFiles/raw/master/package_stmicroelectronics_index.json`

<img src = "https://github.com/CaseFNI/Sensorized-Breakable-Block-and-DLC/blob/main/Docs/Images/BoardManager.png">

Then, press “Ok”.

Now, navigate the top dropdown menu to **Tools** > **Board** > **Board Manager…**

<img src = "https://github.com/CaseFNI/Sensorized-Breakable-Block-and-DLC/blob/main/Docs/Images/Library1.png">

In the search bar of the Boards Manager, type in `STM32 MCU based boards`. A module with this title should be found. Hover the cursor over the bottom right corner of this option, and click the **Install** button when it appears. Once the installation is complete, press **Close**.

Navigate to and select **Tools** > **Board** > **STM32 boards groups** > **Generic STM32F4 series**.

Navigate to and select **Tools** > **Board part number** > **Adafruit Feather STM32F405**.

Navigate to and select **Tools** > **USB support** (if available) > **CDC** (generic ‘Serial’ supersede U(S)ART).

Navigate to and select **Tools** > **Upload Method** > **STM32CubeProgrammer (DFU)**.

#### Library Setup on Arduino IDE
In order to compile the Arduino code (where to obtain this code is described later), certain example libraries must be downloaded to the Arduino IDE.

Go to **Tools** > **Manage Libraries…** and type into the search bar of the Library Manager `STM32duino LIS3MDL`. Hover the cursor over the bottom right corner of this option, and click the **Install** button when it appears. Once the installation is complete, press **Close**.

_If, during installation, a pop-up window appears alerting you of existing dependencies for a particular module, select **Install all** at the bottom of the pop-up window._

Perform the previous step, this time entering `STM32duino LSM6DS3` into the library manager and installing this module.

Perform the previous step, this time entering `STM32duino LIS3MDL`.

Perform the previous step, this time entering `STM32duino STM32SD`.

Perform the previous step, this time entering `Adafruit LIS3MDL`.

Perform the previous step, this time entering `Adafruit LSM6DS`.

#### Installation of STM32CubeProgrammer
Visit the webpage: https://www.st.com/en/development-tools/stm32cubeprog.html.

Upon reaching the above website, select the option “Get Software” at the top of the page, under the heading “STM32CubeProgrammer software for all STM32”.

<img src = "https://github.com/CaseFNI/Sensorized-Breakable-Block-and-DLC/blob/main/Docs/Images/InstallWindow.png">

Then, select “Get Latest” in the row that corresponds to the type of computer being used.

<img src = "https://github.com/CaseFNI/Sensorized-Breakable-Block-and-DLC/blob/main/Docs/Images/STM32Download.png">

After accepting the terms and conditions, you will need to create an ST.com account to acquire the download package. The software will be stored as a .zip file on your computer, so once the download has completed, access the file, right click on it, and select “Extract All”. Once the extraction has completed, open the folder and then open the file, called “SetupSTM32CubeProgrammer...” within it. The setup wizard will then initiate.

Select the “Next” button in the bottom right corner of the setup wizard, and continue to select the standard installation options on the proceeding pages that will bring the wizard to completion.

<img src = "https://github.com/CaseFNI/Sensorized-Breakable-Block-and-DLC/blob/main/Docs/Images/DownloadStart.png">

Finally, at the appearance of the screen reading “Step 8 of 8”, select “Done.” Installation of STM32CubeProgrammer is now complete.

#### Entering Bootloader Mode on the Featherboard

Arrange the Featherboard on a breadboard such that a wire connects the B0 and 3.3V pins; this configuration is known as the “bootloader mode,” and it is employed every time one needs to upload a script to the board.

<img src = "https://github.com/CaseFNI/Sensorized-Breakable-Block-and-DLC/blob/main/Docs/Images/Bootloader.png" width="300">

After obtaining a USB-C to USB cable, plug the USB-C end into the USB-C port on the featherboard and the USB end into a USB port on your computer. No other wires/components should be attached to the featherboard (the IMU can remain connected) at this time.

<img src = "https://github.com/CaseFNI/Sensorized-Breakable-Block-and-DLC/blob/main/Docs/Images/Feather%20Connected%20to%20Computer.png" width="300">

Wait for the featherboard to be detected by your computer. Access the **Device Manager** module of the Control Panel on your computer and check if the **STM32 Bootloader** has appeared. If so, continue on to the next step.

Open the STM32CubeProgrammer application. Ensure that the blue dropdown menu in the top right corner of the application is selected as “USB.”

<img src = "https://github.com/CaseFNI/Sensorized-Breakable-Block-and-DLC/blob/main/Docs/Images/STM32USB.png">

Press the refresh icon located just below this blue dropdown menu, and wait for a connection with the featherboard to be established as denoted by a change in value of the “Port” category from “No DFU detected.”

<img src = "https://github.com/CaseFNI/Sensorized-Breakable-Block-and-DLC/blob/main/Docs/Images/STM32Port.png">

#### Uploading Code to the Featherboard

Open the Arduino IDE. In the top left corner of the application, select File > Open and select the downloaded Arduino file, titled “debug_Final_IMU.ino”, from your computer.

Ensure the featherboard is still in bootloader mode and is connected to the computer, and click the “Upload” button (containing an arrow icon) in the top left corner of the IDE. Wait for the progress bar in the bottom right corner to completely fill.

<img src = "https://github.com/CaseFNI/Sensorized-Breakable-Block-and-DLC/blob/main/Docs/Images/Arduino%20IDE.png" width="600">

The log at the bottom of the IDE should indicate that the download was successfully completed. You may now disconnect the board from bootloader mode by removing the wire connecting B0 and 3.3V. Unplug the USB-C connector between your computer and the featherboard. The featherboard is now ready to be attached to the sensor circuit.

### Installing DLC on Windows
The official instructions are located [here](https://github.com/DeepLabCut/DeepLabCut/blob/master/docs/installation.md)
* If you get stuck you’ll want to refer to that. This is the short version!

#### Install Anaconda and Python
If you already have these installed, you can skip this bit

Go to the [Anaconda website](https://www.anaconda.com/products/individual) and scroll to the dotton until you see the install options shown below

<img src = "https://github.com/CaseFNI/Sensorized-Breakable-Block-and-DLC/blob/main/Docs/Images/Anaconda%20Installer.png">

Install this with the default configuration.

#### Download DLC
The original site for DeepLabCut is located [here](http://www.mousemotorlab.org/deeplabcut)

Scroll down to the download instructions and install the option for the GPU configuration assuming the computer you are using has a GPU.

<img src = "https://github.com/CaseFNI/Sensorized-Breakable-Block-and-DLC/blob/main/Docs/Images/DLC%20Installer.png">

You may also be interested in their [github](https://github.com/DeepLabCut/DeepLabCut).

#### Install DeepLabCut
Find and open **Anaconda Powershell Prompt (anaconda3)**
* This was installed in the the first step, [Install Anaconda and Python](#install-anaconda-and-python).

Find the folder containing `DLC-GPU.yaml`,  shift+right-click and select **Copy as path**

<img src = "https://github.com/CaseFNI/Sensorized-Breakable-Block-and-DLC/blob/main/Docs/Images/Copy%20to%20Path.png">

Now type `cd` and then the path into your prompt window

<img src = "https://github.com/CaseFNI/Sensorized-Breakable-Block-and-DLC/blob/main/Docs/Images/Change%20Directory.png" width="1000">

Now type `conda env create -f DLC-GPU.yaml`.

<img src = "https://github.com/CaseFNI/Sensorized-Breakable-Block-and-DLC/blob/main/Docs/Images/Install%20DLC%20in%20Anaconda.png" width="1000">

This will install DLC. From this point forward, you can access DLC from any directory.

## Breakable Block Set-up
### Breakable Block Circuit 
The circuit of the block will look like what is below when laid out

<img src = "https://github.com/CaseFNI/Sensorized-Breakable-Block-and-DLC/blob/main/Docs/Images/Fritzing%20Circuit.png" width="600">

<img src = "https://github.com/CaseFNI/Sensorized-Breakable-Block-and-DLC/blob/main/Docs/Images/SensorSchematic.png" width="600">

### Soldering Instructions
Begin by arranging the two sets of male headers on a breadboard (long side of the pin in the board) in such a manner as to allow the printed circuit board pinouts to slide on top of the headers. Carefully examine the following two pictures before beginning to solder the pins to the board. (Ignore the JST connectors and resistors attached to the top side of the PCB; attachment of these components will be addressed in subsequent steps.)

The side of the PCB with only 12 pinouts will look as shown below, with all 12 pinouts matching to a male header.

<img src = "https://github.com/CaseFNI/Sensorized-Breakable-Block-and-DLC/blob/main/Docs/Images/PCBSide1.png" width="600">

The side of the PCB with 16 pinouts will look as shown below, with only 9 pinouts matching to a male header. By employing a pair of needle-nosed pliers, one can slide the metal pins out of the black plastic array holding the male headers together. Remove only those pins that have been removed below. By removing these pins, the user will permit access to the 3-pin JST connector added later and shown below.

<img src = "https://github.com/CaseFNI/Sensorized-Breakable-Block-and-DLC/blob/main/Docs/Images/PCBSide2.png" width="600">

Once the unnecessary pins have been removed and the PCB is situated atop all the male headers shown, one may solder the headers to the PCB.

Now, remove the PCB from the breadboard and attach it to the 12- and 16-pin female header sets, and fit the featherboard atop these female headers as shown. (Consider, once again, that the JST connectors and resistors have yet to be attached to the PCB, despite being shown here.) Ensure that the microSD card and IMU have been removed from the featherboard. One may now begin soldering all the female headers to the featherboard.

<img src = "https://github.com/CaseFNI/Sensorized-Breakable-Block-and-DLC/blob/main/Docs/Images/PCBWithFeather.png" width="600">

### Charging the Block
Make sure the lipo battery is charged before beginning the test. At full charge, the battery will produce **4.2V**, and after use the voltage will reduce to **3.7V**. Check the battery with a multimeter, and if the voltage reads 3.7V charge the battery for 2 hours by plugging it into the featherboard while the featherboard is connected to a computer via its USB C port. If the voltage is below 3.7, charge for 4 hours or until voltage returns to 4.2V. Do not leave the battery connected to the board when the board is not in use.

### Connecting the Block
The block lid and base can be completely detached from each other when not in use.

<img src = "https://github.com/CaseFNI/Sensorized-Breakable-Block-and-DLC/blob/main/Docs/Images/Disassembled%20Block.png" width="300">

The Featherboard **cannot** be removed, but it needs to be slid out from the lid to access the USB C port and connect the battery.

Shortly before beginning the test, connect the battery to the block.

<img src = "https://github.com/CaseFNI/Sensorized-Breakable-Block-and-DLC/blob/main/Docs/Images/Check%20Power%20Cable.png" width="300">

Check inside the lid to make sure the red power cables are connected.

Fold all wires into the lid carefully and secure with electrical tape.

<img src = "https://github.com/CaseFNI/Sensorized-Breakable-Block-and-DLC/blob/main/Docs/Images/Connecting%20Purple%20and%20white%20cable%20from%20top%20of%20Block.png" width="100"> <img src = "https://github.com/CaseFNI/Sensorized-Breakable-Block-and-DLC/blob/main/Docs/Images/Purple%20and%20White%20Cables%20in%20Base%20of%20Block.png" width="200">

### Changing Block Strength
The strength of the breakable block can be changed by taking out and replacing its magnetic cartridges. More magnets make the block harder to break. There are cartridges provided to allow for every combination of magnets from 1 to 12.

To remove a cartridge, press the tabs towards the center and pull.

<img src = "https://github.com/CaseFNI/Sensorized-Breakable-Block-and-DLC/blob/main/Docs/Images/Pullin%20out%20Magnets.png" width="300">

When placing the cartridge, always be sure the word “OUT” is on the outside of the block (or the magnets will repel the block).

<img src = "https://github.com/CaseFNI/Sensorized-Breakable-Block-and-DLC/blob/main/Docs/Images/Magnets%20Out.png" width="300">

## Experimental Set-up
DeepLabCut creates neural networks that track visual data. It does not generalize, so it is essential that you follow the experimental set-up exactly whenever you gather data. The following items must be located and placed according to the following directions. Please use the same items used in the original training, and do not substitute them for similar ones as these have been measured and marked with electrical tape.

<img src = "https://github.com/CaseFNI/Sensorized-Breakable-Block-and-DLC/blob/main/Docs/Images/Experimental%20Setup%20Overview.png" width="500">

1. Table
2. Cutting mat
3. Center "net"
4. 2x Net Supports
5. Orange & green calibration markers
6. Faraday curtain
7. Nikon DSLR
8. Camera stand
9. Breakable Block

This experiment must be carried out in the Brain Interface Lab.

Release the right three sections of the Faraday curtain, and then set up the desk according to the electrical tape markings:

<img src = "https://github.com/CaseFNI/Sensorized-Breakable-Block-and-DLC/blob/main/Docs/Images/Floor%20Markers.png" width="500">

Place the cutting mat on the table as indicated by the tape.

Place your experimental components as indicated:

<img src = "https://github.com/CaseFNI/Sensorized-Breakable-Block-and-DLC/blob/main/Docs/Images/Cutting%20Mat.png" width="500">

Set the camera stand to its lowest setting. The legs of the camera stand should now fit between the triad of tape marks on the floor in front of the table.

There is a threaded hole on the bottom of the camera that screws onto the stand.

<img src = "https://github.com/CaseFNI/Sensorized-Breakable-Block-and-DLC/blob/main/Docs/Images/Camera.png" width="200">

Check that the Nikon DSLR has a standard lens attached.

Turn the camera on and press the “Menu” button to adjust the camera settings as shown.

Pulling the lever forward puts the camera in video display mode.

<img src = "https://github.com/CaseFNI/Sensorized-Breakable-Block-and-DLC/blob/main/Docs/Images/Video%20Setup%20Steps.PNG" width="1000">

**Shorter videos are better!** Click record right before the subject lifts the block and stop recording as soon as the subject has released the block.

<img src = "https://github.com/CaseFNI/Sensorized-Breakable-Block-and-DLC/blob/main/Docs/Images/Recording%20Button.png">

Have the subject stand on the opposite side of the table from the camera facing the setup.

# Running the Tests
## Test Procedure
**Two people are required to run this test.** The primary researcher will be stationed at the computer to the left of the table and will be responsible for data collection and calibration. The secondary researcher will be seated directly in front of the table, behind the camera, and will be responsible for stop-watch and camera operation.

Have the subject standing behind the table in line with the net, facing the camera.

1. **Primary researcher:** place the block flat LED-up and pink dot towards the camera on the testing mat starting position. Connect the Grapevine to the breakable block via two wires, one for analog input 1 and the second for the ground. The ground goes to the outer port. Then stand on the computer side of the table facing the camera without obscuring the block

<img src = "https://github.com/CaseFNI/Sensorized-Breakable-Block-and-DLC/blob/main/Docs/Images/Assembled%20Block.png" width="200">

2. **Primary researcher** uses a paperclip to hit **reset button** on the Featherboard inside the block, **secondary researcher** begins stopwatch t=0s
3. **Secondary researcher** begins recording with camera at t=30s
* This is because there is a current delay from reset to the data stream starting 
4. **Primary researcher** presses momentary switch to turn on the LED in the box at t=80s
5. **Primary researcher** disconnects grapevine wires.
6. **Primary researcher** reorients the block to its starting position on its side, pink dot toward the camera

<img src = "https://github.com/CaseFNI/Sensorized-Breakable-Block-and-DLC/blob/main/Docs/Images/Block%20on%20Mat.png" width="400">

7. **Primary researcher** sits at the computer station
8. **Subject** grips the block with the prosthesis such that their fingers are on the lid and their thumb is on the base. The subject must try not to collapse the block while moving it.
9.	**Subject** moves the block over the net and places it on the far target
10.	**Subject** releases their grip and lifts the prosthesis away to indicate the movement is complete
11.	**Subject** grips the block in the same manner as before
12.	**Subject** moves the block over the net and places it back in its starting position
13.	**Subject** releases the block and moves their hand away
14.	**Primary researcher** leaves computer station, reconnects wires to grapevine and presses the calibration button on the block. Try not to obscure pink dot from camera.
15.	**Secondary researcher** stops recording
16.	Wait until t=200s, then stop stopwatch
17.	**Primary researcher** removes SD card from block and inserts it into the computer. Transfer the test data onto the computer, and update the name with a number (Making the first test data “test1.txt”, the second “test2.txt”, etc.)
* This step occurs because the Featherboard is not making new files each time it starts and is not appending to the old file resutling in a error in the code.
18.	**Primary researcher** deletes all files from the SD card and puts the card back in the block. **Primary researcher** may choose to change the cartridges in the block at this time. 
19.	Repeat from step 1.

## Data Collection
### DLC Data
Take the SD card from the DSLR camera and insert it into the computer where you are housing your network. Create a folder within the **DLC**>**BreakableBlockExperiment** and title it with the subject number and date.  Transfer all video files from the SD card into this folder, and rename them all with the subject number, date, and test number. (i.e. S109_20210728_test1). All videos must have unique names.

### Featherboard Data
All files transferred from the SD card will now be stored on the computer and ready for analysis.

### EMG Recording
Either implanted or surface EMG is recorded during the trial as the subject uses a force based controller for the TASKA hand. This EMG data is saved seperatly after each trial.

## Data Analysis
### DLC Analysis
DeepLabCut is software designed for tracking moving subjects. I have already created and trained a network to track our breakable block, so I will only be including instructions for analyzing videos and refining the network to make it stronger and correct mistakes.

**Important note:** All paths require **two** backslashes wherever there would normally be one. Instead of writing a location like this:

`C:\Users\EBME\Desktop\DeepLabCut\BreakableBlock`

you must put:

`C:\\Users\\EBME\\Desktop\\DeepLabCut\\BreakableBlock`

To assist in this, I have a handy little file called **Breakable Block Locations.txt**. There is an adjusted location for the config.yaml file there which you can copy+paste into your code as needed.

When analyzing videos, you will need to add double back-slashes to your path. I recommend copying the path and putting it in the .txt doc, adding the slashes, and then copy+pasting it into your terminal from there.

#### Opening DeepLabCut
1. Open **Anaconda Powershell Prompt (anaconda3)**

<img src = "https://github.com/CaseFNI/Sensorized-Breakable-Block-and-DLC/blob/main/Docs/Images/Open%20Anaconda.png">

_The rest of the steps are letter-for-letter what you type into that box! Remember, capitalization and spaces are important. Click **enter** after each line._

2. `conda activate DLC-GPU`

<img src = "https://github.com/CaseFNI/Sensorized-Breakable-Block-and-DLC/blob/main/Docs/Images/Activate%20DLC.png">

3. `ipython3`

<img src = "https://github.com/CaseFNI/Sensorized-Breakable-Block-and-DLC/blob/main/Docs/Images/Start%20Python.png">

4. `import deeplabcut as dlc`

<img src = "https://github.com/CaseFNI/Sensorized-Breakable-Block-and-DLC/blob/main/Docs/Images/Import%20deeplabcut%20library.png">

That’s it! You’re in. From here skip to whichever action you want to run.

5. When you are done:
 1. exit ipython: `cntrl+d`
 2. `y`
 3. deactivate DLC with: `conda deactivate DLC-GPU`

<img src = "https://github.com/CaseFNI/Sensorized-Breakable-Block-and-DLC/blob/main/Docs/Images/deactivate%20DLC.png">

#### Analyzing a Video
**Always do the previous steps before these**

This takes about 50 seconds for a 30 second video and increases dramatically for longer videos. Multiple videos analyze consecutively.

When you have videos from a test, take them from the camera SIM card to a new folder within **DLC**>**BreakbleBlockTests**.

Rename each video with a unique name and place it in a folder with the same name. I recommend Subject_Date_Vid# (ex: 20210728_S109_1). Multiple files will be generated for each video, and folders will keep them organized.

_If you retrain the network using videos with identical names, the old video will overwrite the new one even if they have different path locations. Most of these videos will not be used for retraining, but I recommend unique informative names anyway._

Now enter `dlc.analyze_videos(”config\\path”,[“Path\\video\\1”,”Path\\video\\2”,…],shuffle=1,save_as_csv=True)`

<img src = "https://github.com/CaseFNI/Sensorized-Breakable-Block-and-DLC/blob/main/Docs/Images/AnalyzeVideo.png" width=700>

This should take ~50 seconds, and it create a .csv and a .h5 file in your folder. This .csv is all you really need here, so if you’re just generating plots, skip ahead to Part 5!

If you want to check the network strength, proceed to Creating Calibrated Plots!

#### Assessing Network Confidence
**The video must be analyzed first.**

This takes about 10 seconds. Multiple videos will run consecutively.

DLC will automatically plot the motion in your video for you and tell you how confident the network is in its analysis. There are instructions for calibrating the data directly from the .csv file into real world time and location data, but these plots could also be useful.

The confidence ratings are extremely useful for deciding whether or not to retrain the network. Ideally you want confidence ratings above 85% for the whole video.

First, enter: `dlc.plot_trajectories(”config\\path”,[“Path\\video\\1”,”Path\\video\\2”,…], shuffle=1)`

_The file path here is the same as the file path in Analyzing a Video!_

This will only take a few seconds. Now open the folder with your video: there will be another folder in there called **“plot poses”**.

<img src = "https://github.com/CaseFNI/Sensorized-Breakable-Block-and-DLC/blob/main/Docs/Images/AllFilesAfterAnalysis.png" width=700>

Inside the folder will be another folder with your video name, and inside that will be 4 graphics.

<img src = "https://github.com/CaseFNI/Sensorized-Breakable-Block-and-DLC/blob/main/Docs/Images/PlotPosesFiles.png" width=700>

These graphics include images of x and y position over time, although this is not calibrated to real world time and space. There is also a likelihood plot.

Perfectly tracked videos will produce liklihood plots like this:

<img src = "https://github.com/CaseFNI/Sensorized-Breakable-Block-and-DLC/blob/main/Docs/Images/plot-likelihood.png" width=500>

Trackings that can be improved will look like this:

<img src = "https://github.com/CaseFNI/Sensorized-Breakable-Block-and-DLC/blob/main/Docs/Images/LikelihoodDipExample.png" width=500>

Videos where the tracked points are covered will look like this:

<img src = "https://github.com/CaseFNI/Sensorized-Breakable-Block-and-DLC/blob/main/Docs/Images/CoveredDotExample.png" width=500>

If you get plots that look like the middle example, you should consider extracting outliers and refining the network.

#### Creating a Labeled Video
**The video must be analyzed first.**

This takes about 1.5x the video length. Multiple videos will run concurrently.

The most satisfying way to review the work of your neural network is to create a labeled video so that you can judge the accuracy of your network for yourself. This function is also good for presenting your work!

Simply enter: `dlc.create_labeled_video(“config\\path”,[“Path\\video\\1”,”Path\\video\\2”,…])`


You can enter as many videos as you want, and as long as you include the full path and have already analyzed each video, you shouldn’t run into any trouble.


<img src = "https://github.com/CaseFNI/Sensorized-Breakable-Block-and-DLC/blob/main/Docs/Images/LabeledVideoWError.png" width=700>

**If you get the error messages seen above, don't worry too much. It does not seem to impede analysis at all.**

When complete, there will be a new video file in the folder with your original video. It will have the same name with the addition of "3DLC_resnet50_BreakableBlockMonthDayshuffle1_200000_labeled".

<img src = "https://github.com/CaseFNI/Sensorized-Breakable-Block-and-DLC/blob/main/Docs/Images/FilesAfterLabeling.png" width=500>

Go ahead and watch it! If your marker is jumping around, you need to do some retraining.

#### Improving the Network
This takes 8 hours or more.

If your results for plots or labeling were unsatisfactory, you will need to extract the bad frames and retrain the network. Heads up, this is very time consuming! Expect to spend a couple of hours extracting and refining, and then retraining will take at least 6 hours. Try to time it so you can let the computer retrain overnight!

Once you have decided to retrain, you will want to find good examples of all the mistakes your network makes. I recommend labeling videos until you have at least two examples of each mistake.

For example, if your video is identifying something on a subject’s shirt instead of the block, try to catch it doing this in at least two different videos. More examples will strengthen the network, so you may want to use four or five examples- especially if the mistake only happens for a few frames in each example.

Once you have your examples, DLC will automatically identify frames in the example videos that have low confidence ratings and extract them for you.

1. Extract Outliers

`dlc.extract_outlier_frames(”config\\path”,[”videofile\\path”])`

This finds all the frames in the chosen video that the computer is not confident about. It will tell you how many there are, and ask if you want to go ahead and extract them. It looks like this:

<img src = "https://github.com/CaseFNI/Sensorized-Breakable-Block-and-DLC/blob/main/Docs/Images/Extract%20Outliers.png" width=700>

If it’s more than 300, you should consider manually labeling instead. If it’s not, tell it you want to continue by entering: `y`

_Time 1-30min depending on number of frames_

It will look like nothing is happening, but just let it do it’s thing until you get your green prompt back. The files you have extracted are now in a folder in your videos folder.

<img src = "https://github.com/CaseFNI/Sensorized-Breakable-Block-and-DLC/blob/main/Docs/Images/ExtractOutliers3.png" width=700>

If you get the warning: "AUTOMATIC ADDING OF VIDEO TO CONFIG FILE FAILED!", you will need to copy the video location as a path and add it to your config.yaml file with the other video files. Match formatting and cropping instructions to other video files.

<img src = "https://github.com/CaseFNI/Sensorized-Breakable-Block-and-DLC/blob/main/Docs/Images/AddToConfig.png" width=400>

I recommend extracting outliers from 2-4 videos before continuing to the next step.

2. Refining your Labels

`dlc.refine_labels(”config\\path”)`

<img src = "https://github.com/CaseFNI/Sensorized-Breakable-Block-and-DLC/blob/main/Docs/Images/RefineFrames0.png" width=500>

A graphic user interface (GUI) will pop up. 

<img src = "https://github.com/CaseFNI/Sensorized-Breakable-Block-and-DLC/blob/main/Docs/Images/Create%20a%20Figure.png" width=500>

 1. Open labeled-data>the video you extracted>machinelabels-iter#.h5
 2.	Choose a likelihood threshold. The example here is 0.40 but you may want to go as high as 0.85 for very strong networks. Markers the computer is less confident in than the value you provide will appear as hollow circles, while the rest will be solid.

<img src = "https://github.com/CaseFNI/Sensorized-Breakable-Block-and-DLC/blob/main/Docs/Images/Show%20Outlier%20Image.png" width=700>

 3. Drag dots that are placed incorrectly to their correct positions with the mouse. You can use the zoom, pan, home, and lock view buttons to get a closer look at the placement if needed.

<img src = "https://github.com/CaseFNI/Sensorized-Breakable-Block-and-DLC/blob/main/Docs/Images/RefineFrames2.png" width=500>

3. Merge Datasets

This command is almost instant, but don’t forget it or your new frames won’t be added to your network.
`dlc.merge_datasets(”config\\path”)`

4. Create Training Dataset

This takes about 20 minutes

`dlc.create_training_dataset(”config\\path”, num_shuffles=1)`

5. Train Network

This takes about 6 hours

`dlc.train_network(”config\\path”,maxiters=200000)`

`maxiters` is the maximum number of iterations the network training goes through. The system reports its progress every 1000 iterations, so you won’t see proof that it’s working for about five minutes. 200000 is the recommended number for a strong network, and after 200000 improvement is negligible. Do not forget the maxiters command! Without it the network will never stop training and you will have to forcibly stop it when you next log on.

There is now a folder named iteration-n in your training-datasets folder, where n=(the previous iteration)+1. Every time you train, the iteration number will increase, and a new folder will appear!

6. Evaluate the Network

This takes about 30 minutes

`dlc.evaluate_network(”config\\path”, plotting=True)`

_This will give you a number that translates to the computer’s confidence in the strength of its new network. You can do some background reading to see how to interpret this, or you can go back to video analysis and see how it performs._

#### Creating Calibrated Plots
DLC automatically generated plots during the Assessing Network Confidence step. However, these plots are not calibrated to real-world time and distance data. In order to calibrate, open the Excel sheet titled "Breakable Block Calibration.xlsx" and the .CSV file generated during the Analyze Video step (It will be called "videoname_resnet50_BreakableBlockDateshuffle1_200000").

Copy columns A through J of your .CSV file and paste them as columns A through J of "Breakable Block Calibration.xlsx". _(it says "paste here")_

The first few rows of real world x and y locations will autopopulate. Highlight these and extend the formatting down until you have "irl" data for all datapoints.

The tabs at the bottom labeled "X vs Time" and "Y vs Time" have graphs which will autopopulate as well.
Save this new file in the video folder under a new name, such as "Vidname_XYPlot".

Use these plots however you want! Nabeel said he would make a better version of this with Python or Matlab in the future, but for now Excel is easy.


#### Transferring your Network
To transfer the network to a new computer, the simplest way is to compress the entire "Breakable Block" folder into a Zip file. The zip file will be about 7 GB, so you will need a fairly large harddrive to transfer it.

Once you have unzipped the folder system onto the new computer, you will need to update the locations in the "config.yaml" file. Update the path and all video file paths. The rest of the locations will be found automatically assuming you have not changed the structure within the folder system at all.

### Featherboard
#### Analysis of Breakable Box MicroSD Card Data with Matlab
After obtaining the necessary Matlab files from GitHub, open the scripts titled `Load_and_Save_Txt` and `MadgwickScript`. Display the script `Load_and_Save_Txt` on the computer screen. To analyze a given data file, on the first line of code (excluding comments), change the file name **20-lateral** in `dlmread(‘20-lateral’, ‘,’)` to the name of the file that you wish to analyze. On the final line of the script, change the file name **20-lateral** in `20-lateral.mat Accelerometer Gyroscope Magnetometer FSR HES time button` to the name of the file you wish to analyze. Initiate the Matlab script by selecting the **Run** icon (a large green triangle).

Next, display the script `MadgwickScript` on the computer screen. Immediately following the commented line `%% Import and plot sensor data`, replace **20-lateral** in the line `load 20-lateral.mat` with the desired file name. Initiate this Matlab script by selecting the **Run** icon.

### EMG Analysis
EMG is used both for the force controller but is also saved to track when the subject made decisions in changing their grip force. **The scripts for this latter part have not been written yet.**

### Combining the Data

# Authors
* **Susaon Oldfeild**-Creato of the test setup, the DLC model, the sensorized block housing, and those corresponding parts of the ReadMe
* **Patrick Pariseau**-Creator of the IMU circuit, programmer of the Featherboard, and writer of the corresponding parts of the ReadMe
* **Nabeel Chowdhury**-Creator of the EMG and Stimulation scripts used with the Grapevine

# Acknowledgments
* [Dustin Tyler Lab](http://engineering.case.edu/ebme/tyler)
* [Mathis Lab](https://www.mackenziemathislab.org/deeplabcut)
