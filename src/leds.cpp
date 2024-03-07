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

#include "leds.h"
#include <Arduino.h>

Leds::Leds(const params::DisplayParams& p):
    led_pin_(p.led_pin),
    number_of_leds_(p.number_of_leds_display),
    magnetometer_led_(p.led_magnetometer),
    location_led_(p.led_location),
    tilt_led_(p.led_tilt),
    reserved_led_(p.led_reserved)
    
{
    leds_ = new CRGB[number_of_leds_];
}

void Leds::init()
{    
    FastLED.addLeds<NEOPIXEL, 9>(leds_, number_of_leds_);  // GRB ordering is assumed, TODO
    FastLED.setBrightness(50);
    reset();
}

void Leds::handleTilt(bool tilt_ok)
{
    if (tilt_ok)
    {
        leds_[tilt_led_] = CRGB::Green;
    }
    else
    {
        leds_[tilt_led_] = CRGB::Red;
    }
}

void Leds::handleLocation(bool location_ok)
{
    if (location_ok)
    {
        leds_[location_led_] = CRGB::Green;
    }
    else
    {
        leds_[location_led_] = CRGB::Red;
    }
}


void Leds::magnetometerCalibrated()
{
    leds_[magnetometer_led_] = CRGB::Green;
}

void Leds::magnetometerCalibrating()
{
    leds_[magnetometer_led_] = CRGB::Yellow;
}

void Leds::magnetometerNotCalibrated()
{
    leds_[magnetometer_led_] = CRGB::Red;
}

void Leds::execute()
{
    FastLED.show();
}

void Leds::reset()
{
    for (int i = 0; i < number_of_leds_; ++i)
    {
        leds_[i] = CRGB::Black;
    }
    FastLED.show();
}