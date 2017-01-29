# Introduction

A tool to allow 1D motion analysis with an arduino and an ultrasonic sensor. This was specifically made to analyze the oscillating motion of a free body mass on a spring.

Built in *Python 2* but may work (or at least not a lot of effort to fix) for *Python 3*!

# Adrduino Setup

![](https://68.media.tumblr.com/7b9be17bca9bfb02f1a775f688ff9e6c/tumblr_inline_okj41jmV201uz3q86_540.png)

The following components (excluding wires) include:
- Arduino Uno
- Ultrasonic Sensor (HC-SR04)
- Temperature Sensor (LM35)
- Push Button
- LEDs (x2)

The temperature sensor is used to calculate the speed of sound in the given room, however not required for the actual motion sensing to work.

In the diagram, the red LED indicates whether the arduino is currently recording measurements and the green LED indicates whether mass is pulled in the range of the desired distance (Default set to 4cm).

The push button is used to start and stop the recording.

# Usage

Before proceeding, ensure you have the following libraries installed!
- `New Ping` for `sonar.ino` 
- `PySerial` for `pyserial.py`

Upload the `sonar.ino` code to the Arduino and once successful, run the `pyserial.py` code which will automatically communicate with the Arduino through the serial. Press the push button to start recording and push it again to stop. After a recording is finished, the measurements will be stored into a csv file. The first column indicates the time elapsed (seconds) and current displacement (meters).

You can use `Trimmer.py` to filter only the points of maximum amplitude and trims out any outliers which may have been misrecorded. To use this, open up your terminal / command prompt and run the file through there with its second parameter as the path to the data recorded.

For example if you have a data file called `recording_1.csv` in the same directory as `Trimmer.py`, you would write in the terminal `./Trimmer.py recording_1.csv`.

