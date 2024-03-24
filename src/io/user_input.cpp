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

#include <Arduino.h>
#include "io/user_input.h"

UserInput::UserInput(SensorHandle& sensors, params::UserInputParams p):
    button_calibration_(p.button_analog_pin, p.button_value_calibration, p.button_read_threshold),
    button_location_save_(p.button_analog_pin, p.button_value_location_save, p.button_read_threshold),
    button_heading_change_(p.button_analog_pin, p.button_value_heading_change, p.button_read_threshold),
    sensors_(sensors)
{

}

void UserInput::init()
{
}

void UserInput::execute()
{
    const auto now = millis();
    readButtons();
    handleCalibrationButton(now);
#ifdef BUILD_WITH_GPS
    handleLocationSaveButton(now);
#endif
}

void UserInput::handleCalibrationButton(long now_ms)
{
    button_calibration_.read();
    if (button_calibration_.isPressed()) 
    {
        if (!button_calibration_.wasPressed())
        {
            // button was just pressed
            calibration_button_pressed_at_ms_ = now_ms;
        }

        if (!calibration_button_needs_release_&&
            now_ms - calibration_button_pressed_at_ms_ > button_wait_time_ms_)
        {
            auto& compass = sensors_.getCompass();
            Serial.println("Requesting magnetometer calibration...");
            compass.requestCalibration();
            calibration_button_needs_release_ = true;
        }
    }
    else
    {
        if (button_calibration_.wasPressed())
        {
            // button was just released
            calibration_button_needs_release_ = false;
        }
    }
}

#ifdef BUILD_WITH_GPS
void UserInput::handleLocationSaveButton(long now_ms)
{
    button_location_save_.read();
    auto& gps = sensors_.getGps();
    if (!gps.isLocationValid())
    {
        return;
    }

    if (button_location_save_.isPressed()) 
    {
        if (!button_location_save_.wasPressed())
        {
            // button was just pressed
            save_location_button_pressed_at_ms_ = now_ms;
        }

        if (!save_location_button_needs_release_ && 
            now_ms - save_location_button_pressed_at_ms_ > button_wait_time_ms_)
        {
            Serial.println("Saving GPS location as target.");
            gps.saveTargetLocation();
            sensors_.savePersistentLocation();
            save_location_button_needs_release_ = true;
        }
    }
    else
    {
        if (button_location_save_.wasPressed())
        {
            // button was just released
            save_location_button_needs_release_ = false;
        }
    }
}
#endif

void UserInput::readButtons()
{
    button_heading_change_.read();
}
