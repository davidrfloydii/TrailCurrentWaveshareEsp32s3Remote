# Project Overview
This project uses the Waveshare ESP32S3 4.3" TouchScreen as a remote control for the TrailCurrent modular system.

Create a file named secrets.h in the src folder with contents similar to below...
```
uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
```

# Case Design
The case is designed to accomodate a battery and buttons for power as well as built in buttons.

![Case Design](ASSETS/CaseDesign.png)