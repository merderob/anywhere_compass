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

#include "Arduino.h"
#include <persistent_storage/persistent_storage.h>
#include <EEPROM.h>

bool PersistentStorage::hasTargetPosition() const
{
    const auto start = EEPROM.read(address_latlon_);
    return start != invalid_start_byte_;
}

gps::LatLon PersistentStorage::getTargetPosition() const
{
    gps::LatLon ret;
    EEPROM.get(address_latlon_, ret);
    return ret;
}

void PersistentStorage::saveTargetPosition(const gps::LatLon& lat_lon) const
{
    Serial.println("Saving location persistently");
    EEPROM.put(address_latlon_, lat_lon);
}

bool PersistentStorage::hastMagneticCalibration() const
{
    const auto start = EEPROM.read(address_magnetic_cali_);
    return start != invalid_start_byte_;
}

compass::Calibration PersistentStorage::getMagneticCalibration() const
{
    compass::Calibration ret;
    EEPROM.get(address_magnetic_cali_, ret);
    return ret;
}

void PersistentStorage::saveMagneticCalibration(const compass::Calibration& calibration) const
{
    Serial.println("Saving magnetic calibration persistently");
    EEPROM.put(address_magnetic_cali_, calibration);
}
