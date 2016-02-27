
/*---Senior Design Project
Dog Activity Monitor
Pin Assignments
X-Axis - A0
Y-Axis - A1
Z-Axis - A2

CS - A2
MOSI - A5
MISO - A4
CK - A3
*/

//Includes
#include "math.h"
#include "blynk/blynk.h"

// This #include statement was automatically added by the Particle IDE.
#include "sd-card-library-photon-compat/sd-card-library-photon-compat.h"

// This #include statement was automatically added by the Particle IDE.
#include "SparkJson/SparkJson.h"

//Pin Definitions
//Accelerometer
int xpin = A0;
int ypin = A1;
int zpin = DAC;

//Hardware SPI
const uint8_t chipSelect = A2;    // Also used for HARDWARE SPI setup
const uint8_t mosiPin = A5;
const uint8_t misoPin = A4;
const uint8_t clockPin = A3;


//SD CARD File
File myFile;


//Blynk Authentication
char auth[] = "399ffb1eefb54e3b99f31fabec9e223a";
//char auth[] = "2dcd06ed4d724632bd739eb98b1e623d";

//Variable Definitions
int xvolt, yvolt, zvolt;
float xaccel, yaccel, zaccel, accel_mag;

int activity_counter=0;
int activity_counter_prev=0;

bool resetFlag = false;

//Timer Configuration
Timer timer(1000, read_accelerometer_value);
Timer activityReset(600000, resetCounter);

void resetCounter()
{
    activity_counter=0;
    /*if(activity_counter-activity_counter_prev==0)
    {
        activity_counter = 0;
    }*/
}
void setup ()
{
    //Serial
    Serial.begin(115200);
    
    //Blynk Initialization
    Blynk.begin(auth);
    
    pinMode(xpin, INPUT);
	pinMode(ypin, INPUT);
	pinMode(zpin, INPUT);
	
	timer.start();
	activityReset.start();
	
    Serial.print("Initializing SD card...");

    if (!SD.begin(chipSelect)){
        Serial.println("Card failed, or not present");
         Blynk.virtualWrite(V1,"Card failed, or not present");
        // don't do anything more:
        return;
    }
    
    Serial.println("initialization done.");
    // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  
}

void read_accelerometer_value()
{
      float zero_g = 2048.0; // expected reading from sensor with no acceleration
      float scale = 409.5; // Steps expected for sensor reading per 1G change
      
      xvolt = analogRead(xpin);
      yvolt = analogRead(ypin);
      zvolt = analogRead(zpin);
      
      xaccel = ((float)xvolt-zero_g)/scale;
      yaccel = ((float)yvolt-zero_g)/scale;
      zaccel = ((float)zvolt-zero_g)/scale;
      
      accel_mag = sqrt((xaccel)*(xaccel)+(yaccel)*(yaccel)+(zaccel)*(zaccel));
      
      if(accel_mag>1.08||accel_mag<0.85)
      {
        activity_counter++;
        //if(activity_counter>=50)
        activity_counter_prev = activity_counter;
        myFile = SD.open("test.txt", FILE_WRITE);
  
        // if the file opened okay, write to it:
        if (myFile) {
            Serial.print("Writing to test.txt...");
            myFile.println(activity_counter);
            // close the file:
            myFile.close();
            Serial.println("done.");
            } else {
                // if the file didn't open, print an error:
                Serial.println("error opening test.txt");
            }
        }
      
    Blynk.virtualWrite(V1, activity_counter);
    Blynk.virtualWrite(V0, activity_counter);
    
}

void loop()
{
    Blynk.run();
    
}
