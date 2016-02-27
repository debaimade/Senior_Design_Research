

/*

Connections:

MPU6050_____UNO
VCC_________3.3v
GND_________GND
SCL_________PinA5
SDA_________PinA4

*/












#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"
#include "Servo.h"
#include "TimerOne.h"


MPU6050 mpu;

int16_t ax, ay, az;
int16_t gx, gy, gz;


double valx, valy, valz;
long prevVal;

double total;
void setup() 
{
    Wire.begin();
    Serial.begin(115200);
    mpu.initialize();
    Timer1.initialize(10000); // Initialize timer1, 10millisecond period
    Timer1.attachInterrupt(datacollect); // collects accelerometer data
    
}

void loop() 
{
    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    
    /*val = map(ax, -17000, 17000, 0, 180);
    val2 = map(ay, -17000, 17000, 0, 180);
    val3 = map(az, -17000, 17000, 0, 180);

    total = sqrt(val*val+val2*val2+val3*val3);
    
    Serial.println(total);
    delay(50);*/
    total = sqrt(valx*valx+valy*valy+valz*valz);
    Serial.println(total);
}

void datacollect()
{
    //mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    valx = map(ax, -17000, 17000, -1, 1);
    valy = map(ay, -17000, 17000, -1, 1);
    valz = map(az, -17000, 17000, -1, 1);

    
    
}


