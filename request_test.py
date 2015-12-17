##Used for testing Python requests on computer rather than on Raspberry Pi

import requests
from PIL import Image
from StringIO import StringIO
import shutil

# # url = 'http://camera-ornament.herokuapp.com/image_processor'
# url = 'http://5724cb70.ngrok.io/image_processor'
# proxyDict = {}
# data = {}
# files = {'image':open('./img/image0.png','rb')}
#
# r = requests.post(url,data=data, files=files, proxies=proxyDict, stream=True)
# with open('./img/this_file.png', 'wb') as out_file:
#     shutil.copyfileobj(r.raw, out_file)
# del r
# i = Image.open(StringIO(r.content))
# i.save("./img/this_file.png")
