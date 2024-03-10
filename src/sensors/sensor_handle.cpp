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

#include "sensors/sensor_handle.h"

SensorHandle::SensorHandle(const PersistentStorage& persistent_storage):
    persistent_storage_(persistent_storage)
{
}

void SensorHandle::init()
{
    imu_.init();
    compass_.init();
#ifdef BUILD_WITH_GPS
    gps_.init();

    if (persistent_storage_.hasTargetPosition())
    {
        Serial.println("Retrieving last saved location from persistent storage");
        const auto target_location = persistent_storage_.getTargetPosition();

        Serial.println("Retrieved target location:");
        Serial.print("lat: "); Serial.println(target_location.lat);
        Serial.print("lon: "); Serial.println(target_location.lon);
        Serial.print("valid: "); Serial.println(target_location.valid);

        gps_.setTargetLocation(target_location);
    }
    else
    {
        Serial.println("Persistent storage has no GPS target position");
    }
#endif

    if (persistent_storage_.hastMagneticCalibration())
    {
        Serial.println("Retrieving magnetic calibration from persistent storage");
        const auto magnetic_calibration = persistent_storage_.getMagneticCalibration();

        Serial.println("Retrieved magnetic calibration:");
        Serial.print("x_offset: "); Serial.println(magnetic_calibration.x_offset);
        Serial.print("y_offset: "); Serial.println(magnetic_calibration.y_offset);
        Serial.print("z_offset: "); Serial.println(magnetic_calibration.z_offset);
        Serial.print("x_scale: "); Serial.println(magnetic_calibration.x_scale);
        Serial.print("y_scale: "); Serial.println(magnetic_calibration.y_scale);
        Serial.print("z_scale: "); Serial.println(magnetic_calibration.z_scale);
        compass_.setCalibration(magnetic_calibration);
    }
    else
    {
        Serial.println("Persistent storage has no magnetic calibration");
    }
}

void SensorHandle::execute()
{
    imu_.execute();
    compass_.execute();
#ifdef BUILD_WITH_GPS
    gps_.execute();
#endif

    if (compass_.canSaveCalibration())
    {
        persistent_storage_.saveMagneticCalibration(compass_.getCalibration());
    }
}

void SensorHandle::savePersistentCalibration()
{
    Serial.println("Saving magnetic calibration persistently");
    persistent_storage_.saveMagneticCalibration(compass_.getCalibration());
}

#ifdef BUILD_WITH_GPS
void SensorHandle::savePersistentLocation() const
{
    if (!gps_.hasTargetLocation())
    {
        Serial.println("Cannot save target location as it is not set.");
        return;
    }
    persistent_storage_.saveTargetPosition(gps_.getTargetLocation());
}
#endif

Imu& SensorHandle::getImu()
{
    return imu_;
}

Compass& SensorHandle::getCompass()
{
    return compass_;
}

#ifdef BUILD_WITH_GPS
Gps& SensorHandle::getGps()
{
    return gps_;
}
#endif
