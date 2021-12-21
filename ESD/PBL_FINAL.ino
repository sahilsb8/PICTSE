#include "I2Cdev.h"
#include "MPU6050.h"

#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE //used as a prerequisite for I2Cdev library
    #include "Wire.h"
#endif
int count = 0;
MPU6050 accelgyro;

int16_t ax, ay, az;
//int16_t gx, gy, gz; //gives values from gyroscopes

#define OUTPUT_READABLE_ACCELGYRO

void setup() {
    #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE //used as a prerequisite for I2Cdev library
        Fastwire::setup(400, true);
    #endif
    Serial.begin(38400);
    Serial.println("Initializing I2C devices...");
    accelgyro.initialize(); //initialize the sensor, included in MPU6050 library
    Serial.println("Testing device connections...");
    Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed"); //Gives status of the sensor
}

void loop() {
    //accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    //accelgyro.getRotation(&gx, &gy, &gz);
    accelgyro.getAcceleration(&ax, &ay, &az);
    if(ax >= 7000) //This value can be adjusted for different conditions
    {
      count++;
      delay(1000);
    }
    #ifdef OUTPUT_READABLE_ACCELGYRO //ifdef is used for conditional compilation
        Serial.print("a/g:\t");
        Serial.print(ax); Serial.print("\t");
        Serial.print(ay); Serial.print("\t");
        Serial.print(az); Serial.print("\tSteps: ");
        Serial.println(count);
    #endif
}
