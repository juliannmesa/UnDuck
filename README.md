
# UnDuck
A Rubber Ducky wireless undetectable kinda thing.
**I am currently waiting for eBay delivering my 32u4, so i am only working on the ESP part right now.**
### Hardware Setup
To set it up, you are going to need: 

 - ESP8266 (module or dev board)
 - Any ATmega32u4 based board, the CJMCU Beetle is recomended
 - Wire (either jumbers or just wire)
 - Soldering station (if you don't plan on using it with a bread board)
Assembly process on the wiki: HERE (Todo)

### Software Setup
Again, you are going to need:

 - Arduino IDE
   - ESP8266 core for arduino
 - USB to TTL converter (needed if you are using a ESP8266 module)
Instalation process on the wiki: HERE (Todo)
### Using the thing
This will support
 - Running DuckyScript direcly off the website
 - Saving DuckyScript to ram, and executing it as many times as you want while it is still turned on
 - Saving DuckyScript to internal flash, external flash or an SD card and executing those scripts
 - Executing a built-in script that will download an exe file that will intercept this Ducky's keystrokes and comunicating back to the Ducky via the intercepted LEDs, so that you can have a seamless shell
 - Uploading other files, which the Ducky will type in, and execute either directly, or via powershell/cmd/wscript/cscript

#### Thanks acrobotic for the server base!
#### Thanks Seytonic for the Ducky interpreter!