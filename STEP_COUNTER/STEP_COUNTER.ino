
#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"
#include "Servo.h"

MPU6050 mpu;

int16_t ax, ay, az;
int16_t gx, gy, gz;


long val_x, val_y, val_z;
//long prevVal;

float threshhold =80.0;

float xval[100] = {0};
float yval[100] = {0};
float zval[100] = {0};

float xavg, yavg, zavg;
int steps, flag = 0;


void setup() 
{
    Wire.begin();
    Serial.begin(9600);
    mpu.initialize();
    
}


void loop() {
  // put your main code here, to run repeatedly:
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  int acc=0;
  float totvect[100]={0};
  float totave[100]={0};
  float xaccl[100]={0};
  float yaccl[100]={0};
  float zaccl[100]={0};

  for (int i=0;i<100;i++)
  {
    xaccl[i]=float(ax);
    delay(1);
    yaccl[i]=float(ay);
    delay(1);
    zaccl[i]=float(az);
    delay(1);

    totvect[i] = sqrt(((xaccl[i]-xavg)*(xaccl[i]-xavg))+ ((yaccl[i] - yavg)*(yaccl[i] - yavg)) + ((zval[i] - zavg)*(zval[i] - zavg)));
    totave[i] = (totvect[i] + totvect[i-1]) / 2 ;
    //Serial.println(totave[i]);
    delay(50);

    //cal steps 
    /*if (totave[i]>threshhold && flag==0)
    {
      steps=steps+1;
      flag=1;
 
    }
    else if (totave[i] > threshhold && flag==1)
    {
    //do nothing 
    }
    if (totave[i] <threshhold  && flag==1)
    {flag=0;}*/
    Serial.println('\n');
    Serial.println(steps);
    
     
}
  }
  

