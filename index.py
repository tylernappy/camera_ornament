import os
import os, os.path
from threading import Thread
import time
import picamera
import requests
import shutil
from havenondemand.hodindex import HODClient

##Haven OnDemand client
client = HODClient("http://api.havenondemand.com", "API_KEY")

##Find number of images already saved
##Need for if Raspberry Pi shuts off and im_counter gets set back to zero
DIR = './img' #directory images get saved to
img_counter = len([name for name in os.listdir(DIR) if os.path.isfile(os.path.join(DIR, name))])
##

##Set constants
slideshow_delay = 30
save_and_display_delay = 40
img_name = 'image'

##Initialize camera
camera = picamera.PiCamera()
camera.sharpness = 0
camera.contrast = 0
camera.brightness = 50
camera.saturation = 0
camera.ISO = 0
camera.video_stabilization = False
camera.exposure_compensation = 0
camera.exposure_mode = 'auto'
camera.meter_mode = 'average'
camera.awb_mode = 'auto'
camera.image_effect = 'none'
camera.color_effects = None
camera.rotation = 0
camera.hflip = False
camera.vflip = False
camera.crop = (0.0, 0.0, 1.0, 1.0)
time.sleep(0.5)
camera.capture('./img/' + img_name + str(img_counter) + '.png')
##


## Initializing
print "Initializing..."
time.sleep(2)
##

## repeat over and over again - Thread 1
def check_for_faces():
	global img_counter
	while True:
		camera.capture('image_temp.png')
		r_HOD = client.post('detectfaces', files = {'file': open('./image_temp.png', 'rb')})
		print "------------"
		print "POST to HOD"
		if len(r_HOD.json()['face']) > 0: # is there a face in the image
			print "Face(s) detected"
			## POST to NeoPixel; turn light on signaling it's working
			r = requests.post('https://api.particle.io/v1/devices/<core_id>/start', data={'access_token': '<access_token>', 'arg': "test"}, stream=True)
			##
			## POST to Node.js server for image processesing
			url = 'http://camera-ornament.herokuapp.com/image_processor'
			proxyDict = {}
			data = {}
			files = {'image':open('./image_temp.png','rb')}
			r_server = requests.post(url, data=data, files=files, proxies=proxyDict, stream=True)
			##
			## Save image locally
			with open('./img/' + img_name + str(img_counter) + '.png', 'wb') as out_file:
			    shutil.copyfileobj(r_server.raw, out_file)
			del r_server
			##
			os.system('sudo fbi -T 2 -d /dev/fb1 -noverbose -a ./img/' + img_name + str(img_counter) + '.png') #display image
			img_counter += 1 # increment counter of image (first picture will overwrite initialized image)
			time.sleep(save_and_display_delay)
		else:
			print "No face(s) detected"

## repeat over and over again - Thead 2
def slide_show():
	while True:
		# Loop through each image and display
		for i in range(0, img_counter+1):
			print 'Viewing ' + img_name + str(i) + '.png'
			os.system('sudo fbi -T 2 -d /dev/fb1 -noverbose -a ./img/' + img_name + str(i) + '.png')
			time.sleep(slideshow_delay)

##Set threads
t1 = Thread(target = check_for_faces)
t2 = Thread(target = slide_show)

t1.daemon = True
t2.daemon = True

t1.start()
t2.start()
##

## Keep everything running
while True:
	time.sleep(0.001)
