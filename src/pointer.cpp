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
#include "utils.h"

void Pointer::init()
{
    FastLED.addLeds<NEOPIXEL, 3>(leds, 16);  // GRB ordering is assumed
    FastLED.setBrightness(50);
    reset();
}

void Pointer::pointToNorth()
{
    const auto led_to_north = round(azimuth_ / (2 *M_PI) * 16.0f);
    if (led_to_north < 0 || led_to_north >= 16)
    {
        Serial.println(led_to_north);
        return;
    }
    
    if (active_led_ != led_to_north)
    {
        if (active_led_ != -1)
        {
            leds[active_led_] = CRGB::Black;
        }

        leds[led_to_north] = CRGB::White;
        FastLED.show();
        active_led_ = led_to_north;
    }
}

void Pointer::execute()
{
    if (!enabled_)
    {
        return;
    }
    pointToNorth();
}

void Pointer::enable()
{
    enabled_ = true;
}

void Pointer::disable()
{
    if (enabled_)
    {    
        reset();
        active_led_ = -1;
        enabled_ = false;
    }
}

void Pointer::reset()
{
    for (int i = 0; i < Pointer::number_of_leds; ++i)
    {
        leds[i] = CRGB::Black;
        FastLED.show();
    }
}

void Pointer::setLatLon(const Gps::LatLon& latlon)
{
    latlon_ = latlon; 
}

void Pointer::setAzimuth(int azimuth_deg)
{
    azimuth_ = utils::degToRad(azimuth_deg);
}
