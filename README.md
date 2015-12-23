# IoT Holiday Camera Ornament

![Awesome gif](./how_to_gif.gif?raw=true)

**[Check out this blog post for more information and how to build it.](https://community.havenondemand.com/t5/Blog/IoT-Holiday-Camera-Ornament-using-Face-Detection-Raspberry-Pi/ba-p/2484)**

## What is this IoT holiday camera ornament you speak of?
This holiday ornament hangs up on whatever festive item you use during the holiday season (e.g. Christmas tree, Menorah, Kinara, etc.). Attached to the ornament is a screen which plays a slideshow on loop of pictures taken of people viewing or posing in front of the tree with a superimposed holiday greeting, so your friends and loved ones will be with you every step of the way throughout the holiday season. Coupled with this is a ring of NeoPixels, powered by a Particle Core, that plays different light shows on loop which can be used as additional ornament or tree topper.

## How does it work?
The ornament is a Raspberry Pi with a camera module, Wifi dongle, and 3.5 inch display attached to its face. The camera takes pictures at set time intervals of anyone looking, or posing, in front of the tree. It then pushes this image to Haven OnDemand's Face Detection API to validate if there was, infact, a person, or people, in front of the tree. If someone is detected in the image, the image gets sent over to a Node.js server which superimposes a holiday greeting in unique holiday colors and fonts. While it’s doing this, the ring of Neopixels displays a buffering sign so the people getting their picture taken know their image is in the works and will display shortly. Once the new image is finished processing, it gets received by the Raspberry Pi and immediately displays it on the 3.5 inch display and adds it to the looping slideshow of previously taken pictures.

## Hardware needed to construct
* For the Raspberry Pi display ornament:
  * [Raspberry Pi (I used a model B, but you can use any other future version)](https://www.adafruit.com/products/998)
  * [SD card (4GB or more)](https://www.adafruit.com/products/1294)
  * [Wifi dongle](https://www.adafruit.com/products/814)
  * [3.5 inch display](https://www.adafruit.com/products/2441)
  * [Raspberry Pi camera module](https://www.adafruit.com/products/1367)
  * [Camera module support](https://www.adafruit.com/products/1434)
* For the Neopixel ring light signals:
  * Particle Core (although the new [Photon](https://www.adafruit.com/products/2721) should work fine)
  * [NeoPixel Ring (can use any arrangement of NeoPixels)](https://www.adafruit.com/products/2268)

## Software libraries/APIs needed to construct
* For the Raspberry Pi display ornament:
  * [Haven OnDemand Face Detection API](https://dev.havenondemand.com/apis/detectfaces#overview)
  * [Haven OnDemand Python client library](https://github.com/HPE-Haven-OnDemand/havenondemand-python)
  * Python - for Raspberry Pi
* For the Node.js server:
  * [Express](http://expressjs.com/en/index.html)
  * [GraphicMagick](http://aheckmann.github.io/gm/)
  * [Multer](https://github.com/expressjs/multer)
  * [Sleep](https://www.npmjs.com/package/sleep)
  * [ngork](https://ngrok.com/)
* For the Neopixel ring light signals:
  * [NeoPixel for Particle](https://github.com/technobly/SparkCore-NeoPixel)
