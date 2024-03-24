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

#include "io/analog_button.h"
#include <Arduino.h>

AnalogButton::AnalogButton(int pin, int nominal_value, int threshold):
    pin_(pin), nominal_value_(nominal_value), threshold_(threshold)
{
    pinMode(pin_, INPUT);
}

void AnalogButton::read()
{
    was_pressed_ = is_pressed_;
    const auto button_value = analogRead(pin_);
    is_pressed_ = ((nominal_value_ - threshold_) < button_value) && (button_value < (nominal_value_ + threshold_));
}

bool AnalogButton::isPressed() const
{
    return is_pressed_;
}

bool AnalogButton::wasPressed() const
{
    return was_pressed_;
}
