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

#include <FastLED.h>
#include "sensors/gps.h"

class Pointer
{
public:
    Pointer(const params::DisplayParams& p);
    void init();
    void execute();

    void enable();
    void disable();
    void reset();

    void setLatLon(const Gps::LatLon& latlon);
    void setAzimuth(int azimuth_deg);

    void pointToNorth();

private:
    int pointer_pin_ = 8;
    int number_of_leds_ = 16; 
    CRGB* leds_;

    bool enabled_ = false;
    Gps::LatLon latlon_;
    /// @brief Azimuth [0; 2pi]
    float azimuth_ = 0;
    int active_led_ = -1;
};
