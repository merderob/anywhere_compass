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

void SensorHandle::init()
{
    imu_.init();
    compass_.init();
#ifdef BUILD_WITH_GPS
    gps_.init();
#endif

}


void SensorHandle::execute()
{
    imu_.execute();
    compass_.execute();
#ifdef BUILD_WITH_GPS
    gps_.execute();
#endif
}

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
