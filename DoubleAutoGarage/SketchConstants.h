#pragma once

/*
	This header's file contain the constant of sketch.
	Please, don't touch ther because they are directly related to hardware
*/

#define PIN_RELE_UP_1 12
#define PIN_RELE_DOWN_1 13
#define PIN_RELE_UP_2 10
#define PIN_RELE_DOWN_2 9
#define PIN_SENSOR_UP_1 8
#define PIN_SENSOR_DOWN_2 7
#define PIN_SENSOR_UP_2 6
#define PIN_SENSOR_DOWN_2 5

#define PIN_433_RX 2 // This must to be setted on 2nd pin beceause the data 
                     // receive is based on interrupt on this pin

// RadioCommands' code
const unsigned long CODE_UP_1 = 15524904; // TODO You must change this!!! DEFAULT !!!
const unsigned long CODE_DOWN_1 = 123456789; // TODO You must change this!!! FAKE !!!
const unsigned long CODE_UP_2 = 123456789; // TODO You must change this!!! FAKE !!!
const unsigned long CODE_DOWN_2 = 123456789; // TODO You must change this!!! FAKE !!!

// Max Height
const unsigned long int  HEIGHT_TIME_1 = 2 * 1000; // TODO Thinging it! 
const unsigned long int  HEIGHT_TIME_2 = 5 * 1000; // TODO Thinging it!

