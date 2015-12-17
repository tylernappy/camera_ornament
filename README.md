# Christmas Tree Camera Ornament
Ornament that hangs on your tree that takes pictures of lookers, if faces are detected in the image - formats them with a superimposing holiday greeting, and adds to the slide show playing on the ornament's screen.

## Libraries used
* Raspberry Pi
* [PiTFT - Assembled 480x320 3.5" TFT+Touchscreen for Raspberry Pi](http://www.adafruit.com/products/2097)
* [Raspberry Pi Camera Board](http://www.adafruit.com/products/1367)
* [Haven OnDemand Face Detection API](https://dev.havenondemand.com/apis/detectfaces#overview)

## Screen
### [Install screen firmware](https://learn.adafruit.com/adafruit-pitft-3-dot-5-touch-screen-for-raspberry-pi/easy-install)
Download the software

    wget http://adafru.it/pitftsh
    mv pitftsh pitft.sh
    chmod +x pitft.sh
Run it

    sudo ./pitft.sh -t 35r -r
Reboot the Pi

    sudo reboot

Everything should display on the Pi



### [Install video viewing software](https://learn.adafruit.com/adafruit-pitft-3-dot-5-touch-screen-for-raspberry-pi/displaying-images)
    sudo apt-get install fbi
View images with the following syntax

    sudo fbi -T 2 -d /dev/fb1 -noverbose -a adapiluv480x320.png
