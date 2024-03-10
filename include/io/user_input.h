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

#include <utils/params.h>
#include <sensors/sensor_handle.h>

class UserInput 
{
public:
    UserInput(SensorHandle& sensors, params::UserInputParams p ={});
    void init();
    void execute();
private:
    int button_pin_calibration_ = 0;
    int prev_button_state_calibration_ = 0;  
    long calibration_button_pressed_at_ms_ = 0;
    bool calibration_button_needs_release_ = false;

    int button_pin_location_save_ = 0;
    int prev_button_state_location_save_ = 0;
    long save_location_button_pressed_at_ms_ = 0;
    bool save_location_button_needs_release_ = false;

    const long button_wait_time_ms_ = 3000; // 3s

    /// @brief Reference to the sensor handler instance.
    SensorHandle& sensors_;

    void handleCalibrationButton(long execution_time_ms);
#ifdef BUILD_WITH_GPS
    void handleLocationSaveButton(long execution_time_ms);
#endif
    bool isPressed(int button_pin) const;
    int readButton(int button_pin) const;
};
