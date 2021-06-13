# physical_variables_monitoring
This is a final project for the Instrumentacion Electronica course for 8th semester, it includes a mysql database script, an arduino algorithm and node.js server.

#Arduino
This is a very basic algorithm that allow a arduino to use ESP32 Wifi Driver for send to a server data about temperature (DHT11), vibrations (SW420) and monitoring when a proximit y sensor is activated (FC51).
#Node JS
This mini server is an API for receive the data from Arduino, it includes endpoints which allow a user to get the processed data.
#MySQL
A mini script to build de database for connect with the NodeJS server

YOU NEED A .ENV FILE TO MAKE THIS REPOSITORY WORK.
