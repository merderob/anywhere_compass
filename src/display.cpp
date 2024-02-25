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

#include "display.h"
#include <Arduino.h>

Display::Display(SensorHandle& sensors, params::DisplayParams p):
    sensors_(sensors),
    leds_(p)
{
}


void Display::init()
{
    Serial.println("Initializing display");
    pointer_.init();
    leds_.init();
    Serial.println("Display initialized.");
}

void Display::handlePointer()
{
    const auto& imu = sensors_.getImu();
    const auto& compass = sensors_.getCompass();
#ifdef BUILD_WITH_GPS
    const auto& gps = sensors_.getGps();
    if (!imu.checkTilt() ||  !compass.calibrated() || !gps.isLocationValid() )
#else
    if (!imu.checkTilt() ||  !compass.calibrated())
#endif
    {
        pointer_.disable();
        return;
    }

    pointer_.enable();
#ifdef BUILD_WITH_GPS
    pointer_.setLatLon(gps.getLatLon());
#endif
    pointer_.setAzimuth(compass.getAzimuith());
    pointer_.execute();
}

void Display::handleLeds()
{
    if (sensors_.getImu().checkTilt())
    {
        leds_.tiltOk();
    }
    else
    {
        leds_.tiltError();
    }

#ifdef BUILD_WITH_GPS
    if (sensors_.getGps().isLocationValid())
    {
        leds_.validLocation();
    }
    else
    {
        leds_.invalidLocation();
    }
#else
    leds_.validLocation();
#endif

    const auto magn_state = sensors_.getCompass().getState();
    switch (magn_state)
    {
    case Compass::State::UNCALIBRATED:
        leds_.magnetometerNotCalibrated();
        break;
    case Compass::State::CALIBRATION_REQUESTED:
        leds_.magnetometerCalibrating();
        break;
    case Compass::State::CALIBRATING:
        leds_.magnetometerCalibrating();
        break;
    case Compass::State::CALIBRATED:
        leds_.magnetometerCalibrated();
        break;
    }
}

void Display::execute()
{
    handlePointer();
    handleLeds();
}
