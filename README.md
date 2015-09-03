To get this to compile.. copy the AdafruitIOKey-Example.h file to 
AdafruitIOKey.h and WiFiPassword-Example.h to WiFiPassword.h.

You'll need to edit the files at that point to update the username,
passwords and server information as well as SSIDs.

Note - you can use this with any MQTT serer - just change the AIO_* 
values to match your server.  (AIO_KEY is the password.)


IMPORTANT - I have not updated the code.  You will need to change the 

#define FEED_PATH "tomn46037/feeds/cube-"

entry in the *.ino file.  The "tomn46037" shoud be replaced with 
YOUR Adafruit IO username.  If you are using your own MQTT server, 
you can use whatever FEED_PATH you want.