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

#include <stdint.h>

namespace params
{

struct ImuParams
{
    /// @brief Accelerometer sensitivity with default +/- 2g scale
    float accelerometer_sensitivity = 16384.0; 
    /// @brief Gyroscope sensitivity with default +/- 250 deg/s scale
    float gyrocope_sensitivity  = 131.0;   
};

struct CompassParams
{
    /// @brief  @brief Magnetic declination (degree part) valid for Budapest.
    int magnetic_declination_degrees = 5;
    /// @brief  @brief Magnetic declination (minute part) valid for Budapest.
    uint8_t magnetic_declination_minutes = 40;
};

struct GpsParams
{
    int rx_pin = 12;
    int tx_pin = 11;
    long gps_baud = 9600;
};

struct UserInputParams
{   
    /// @brief The pin for the analog button inputs.
    int button_analog_pin = 54;
    /// @brief brief The nominal value of the analog input for the "calibration" button.
    int button_value_calibration = 928; 
    /// @brief brief The nominal value of the analog input for the "location save" button.
    int button_value_location_save = 1002; 
    /// @brief brief The nominal value of the analog input for the "heading change" button.
    int button_value_heading_change = 1012;
    /// @brief The threshold in which the analog values are accepted.
    int button_read_threshold = 5;
    /// @brief The time required for a button push to be accepted.
    long button_wait_time_ms = 2000; // 2s
};


struct DisplayParams
{
    // Pointer-related parameters
    int pointer_led = 8; 
    int number_of_leds_pointer = 16;

    // Leds-related parameters
    int led_pin = 9;
    int number_of_leds_display = 4;
    int led_magnetometer = 0;
    int led_location = 1;
    int led_tilt = 2;
    int target_location_set = 3;
};

struct DebugParams 
{
    static const int serial_baud_rate = 9600;
};

}
