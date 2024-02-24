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


#include "pointer.h"

Pointer::Pointer(const Imu& imu, const Compass& compass, const Gps& gps):
    imu_(imu),
    compass_(compass),
    gps_(gps)
{
    FastLED.addLeds<NEOPIXEL, 3>(leds, 16);  // GRB ordering is assumed
    FastLED.setBrightness(50);
}

void Pointer::execute()
{
    if (gps_.isLocationValid() && compass_.calibrated())
    {
        enabled = true;
    }

    const auto min = 0;
    const auto max = 4;
    if (enabled)
    {
        int randNum = rand()%(max-min + 1) + min;
        // Turn the LED on, then pause
        leds[4] = colors[randNum];
        FastLED.show();
    }
    else
    {
        leds[4] = CRGB::Black;
        FastLED.show();
    }
}
