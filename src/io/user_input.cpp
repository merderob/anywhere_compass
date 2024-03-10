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
    button_pin_calibration_(p.button_pin_calibration),
    button_pin_location_save_(p.button_pin_location_save),
    sensors_(sensors)
{

}

void UserInput::init()
{
    pinMode(button_pin_calibration_, INPUT);
    pinMode(button_pin_location_save_, INPUT);
}

void UserInput::execute()
{
    const auto now = millis();
    handleCalibrationButton(now);
#ifdef BUILD_WITH_GPS
    handleLocationSaveButton(now);
#endif
}

void UserInput::handleCalibrationButton(long now_ms)
{
    const auto calibration_button_state = readButton(button_pin_calibration_);
    if (calibration_button_state == HIGH) 
    {
        if (prev_button_state_calibration_ == LOW)
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
        if (prev_button_state_calibration_ == HIGH)
        {
            // button was just released
            calibration_button_needs_release_ = false;
        }
    }
    prev_button_state_calibration_ = calibration_button_state;
}

#ifdef BUILD_WITH_GPS
void UserInput::handleLocationSaveButton(long now_ms)
{
    auto& gps = sensors_.getGps();
    if (!gps.isLocationValid())
    {
        Serial.println("Gps location is not valid - cannot save it.");
        return;
    }

    const auto location_save_button_state = readButton(button_pin_location_save_);
    if (location_save_button_state == HIGH) 
    {
        if (prev_button_state_location_save_ == LOW)
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
        if (prev_button_state_location_save_ == HIGH)
        {
            // button was just released
            save_location_button_needs_release_ = false;
        }
    }
    prev_button_state_location_save_ = location_save_button_state;
}
#endif

bool UserInput::isPressed(int button_pin) const
{
    const auto button_state =  readButton(button_pin);
    return button_state == HIGH;
}

int UserInput::readButton(int button_pin) const
{
    return digitalRead(button_pin);
}
