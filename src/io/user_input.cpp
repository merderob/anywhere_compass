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
    sensors_(sensors)
{

}

void UserInput::init()
{
    pinMode(button_pin_calibration_, INPUT);
}

void UserInput::execute()
{
    button_state_calibration_ = digitalRead(button_pin_calibration_);
    if (button_state_calibration_ == HIGH) 
    {
        auto& compass = sensors_.getCompass();
        if (!compass.calibrated() && compass.getState() != Compass::State::CALIBRATING)
        {
            Serial.println("Requesting magnetometer calibration...");
            compass.requestCalibration();
        }
        else
        {
            Serial.println("Magnetometer is already calibrated.");
        }
    }
}