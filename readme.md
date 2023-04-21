# espcron
Use to turn on specific nodemcu pin at customizable time with beautiful web UI.

# Features
Read the code. As a wise man once said 
> ผมต้องการส่งเสริมให้คนศึกษาจากโค้ด ผมมองว่าการศึกษาจากโค้ดโดยตรงเป็นวิธีที่เหมาะสมที่สุด

# Software setup
You need Arduino CLI to build this as well as the ESP platform and Ticker library as arduino Dependecies    
For `webbuiltin.hpp` tou can just copy paste whatever inside `/web/src` to that file or if you prefered auto build then you need node installed as well


# Hardware setup
- ESP8266
- DS1302 Clock module
- Something connect to controlled pin e.g. led, relay     
For more info read [features](#features)

# Project status
Now it can control 2 pin that shared same state. 
This project currently in alpha and look like it'll always be.
*Now I'm regret that I write the frontend in vanilla javascript*
