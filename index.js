var express = require('express')
var app = express()
var multer  = require('multer')
var upload = multer({ dest: 'uploads/' })
var port = process.env.PORT || 5000
var fs = require('fs')
  , gm = require('gm').subClass({imageMagick: true})
var sleep = require('sleep')

var fontOptions = ["1", "2", "3", "4"]
var strokeOptions = ["white", "blue", "red", "green"]
var fillOptions = ["white", "blue", "red", "green"]
var borderOptions = ["white", "red", "green"]
var greetingOptions = ["Merry Christmas", "Happy Holidays"]


app.post("/image_processor", upload.single('image'), function(req, res, next) {
  var variables = determineVars()
  createImage(req.file.path, variables)
  sleep.sleep(3)
  fs.unlink(req.file.path)
  res.sendFile(__dirname + "/outgoing_images/outgoing_image.png")
})


app.listen(port, function(){
  console.log("Listening on port: " + port)
})

// functions
createImage = function(image, dict) {
  gm(image)
  .font('./fonts/' + dict.font + '.ttf').fontSize(80).stroke(dict.stroke, 2).fill(dict.fill).drawText(0, 20, dict.greeting, "South")
  .borderColor(dict.border).border(20, 20)
  .write("./outgoing_images/outgoing_image.png", function (err) {
    if (!err) console.log('done')
  })
}

determineVars = function() {
  var font = determineValue(fontOptions)
  var stroke = determineValue(strokeOptions)
  var fill = determineValue(fillOptions)
  var border = determineValue(borderOptions)
  var greeting = determineValue(greetingOptions)
  return {font: font, stroke: stroke, fill: fill, border: border, greeting: greeting}
}

// helper function of determineVars()
determineValue= function(arr) {
  var max = arr.length
  var min = 0
  var index = Math.floor(Math.random() * (max - min)) + min
  var value = arr[index]
  return value
}
