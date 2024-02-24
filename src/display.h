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

#pragma once

#include "imu.h"
#include "compass.h"
#include "gps.h"

class Display
{
public:
    Display(const Imu& imu, const Compass& compass, const Gps& gps, params::DisplayParams p = {});
    void init() const;
    void execute();

    void validLocation() const;
    void invalidLocation() const;

    void tiltOk() const;
    void tiltError() const;

    void magnetometerCalibrated() const;
    void magnetometerCalibrating() const;
    void magnetometerNotCalibrated() const;

private:
    void locationLedGreenOff() const;
    void locationLedGreenOn() const;
    void locationLedRedOn() const;
    void locationLedRedOff() const;

    void tiltLedGreenOff() const;
    void tiltLedGreenOn() const;
    void tiltLedRedOff() const;
    void tiltLedRedOn() const;

    void magnetometerLedGreenOff() const;
    void magnetometerLedGreenOn() const;
    void magnetometerLedRedOff() const;
    void magnetometerLedRedOn() const;

    int green_led_location_ = 0;
    int red_led_location_ = 0;
    int green_led_tilt_ = 0;
    int red_led_tilt_ = 0;
    int green_led_magnetometer_ = 0;
    int red_led_magnetometer_ = 0;

    /// @brief Reference to the IMU instace.
    const Imu& imu_;
    /// @brief Reference to the Compass instace.
    const Compass& compass_;
    /// @brief Reference to the GPS instance.
    const Gps& gps_;
    
};
