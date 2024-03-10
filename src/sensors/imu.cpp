// Copyright © 2024 Robert Takacs
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation
// files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy,
// modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software
// is furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE 
// WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include "sensors/imu.h"
#include <Arduino.h>
#include <math.h>

#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif

Imu::Imu(params::ImuParams p):
    accelerometer_sensitivity_(p.accelerometer_sensitivity),
    gyrocope_sensitivity_(p.gyrocope_sensitivity)
{

}


void Imu::init()
{
    Serial.println("Initializing IMU");
    // join I2C bus (I2Cdev library doesn't do this automatically)
    #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif

    sensor_.initialize();

    // verify connection
    initialized_ = sensor_.testConnection();
    Serial.println(initialized_ ? "IMU initialization successful" : "IMU initialization failed");
    sensor_.setI2CBypassEnabled(true); // set bypass mode
}

void Imu::execute()
{
    // read raw accel/gyro measurements from device
    sensor_.getMotion6(&ax_, &ay_, &az_, &gx_, &gy_, &gz_);
}

bool Imu::checkTilt() const
{
    const auto t =  8 * sqrt(pow(ax_, 2) + pow(ay_, 2)) ;
    return abs(az_) > t;
}

void Imu::log()
{
        #ifdef OUTPUT_READABLE_ACCELGYRO
        // display tab-separated accel/gyro x/y/z values
        Serial.print("a/g:\t");
        Serial.print(ax_); Serial.print("\t");
        Serial.print(ay_); Serial.print("\t");
        Serial.print(az_); Serial.print("\t");
        Serial.print(gx_); Serial.print("\t");
        Serial.print(gy_); Serial.print("\t");
        Serial.println(gz_);

        // Serial.print(ax/accelerometer_sensitivity_); Serial.print("\t");
        // Serial.print(ay/accelerometer_sensitivity_); Serial.print("\t");
        // Serial.print(az/accelerometer_sensitivity_); Serial.print("\t");
        // Serial.print(gx/gyrocope_sensitivity_; Serial.print("\t");
        // Serial.print(gy/gyrocope_sensitivity_); Serial.print("\t");
        // Serial.print(gz/gyrocope_sensitivity_); Serial.print("\t");
    #endif

    #ifdef OUTPUT_BINARY_ACCELGYRO
        Serial.write((uint8_t)(ax >> 8)); Serial.write((uint8_t)(ax & 0xFF));
        Serial.write((uint8_t)(ay >> 8)); Serial.write((uint8_t)(ay & 0xFF));
        Serial.write((uint8_t)(az >> 8)); Serial.write((uint8_t)(az & 0xFF));
        Serial.write((uint8_t)(gx >> 8)); Serial.write((uint8_t)(gx & 0xFF));
        Serial.write((uint8_t)(gy >> 8)); Serial.write((uint8_t)(gy & 0xFF));
        Serial.write((uint8_t)(gz >> 8)); Serial.write((uint8_t)(gz & 0xFF));
    #endif
}
