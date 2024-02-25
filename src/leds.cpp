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
    green_led_location_(p.green_led_location), 
    red_led_location_(p.red_led_location),
    green_led_tilt_(p.green_led_tilt),
    red_led_tilt_(p.red_led_tilt),
    green_led_magnetometer_(p.green_led_magnetometer),
    red_led_magnetometer_(p.red_led_magnetometer)
{
}

void Leds::init() const
{
    pinMode(green_led_location_, OUTPUT);
    pinMode(red_led_location_, OUTPUT);
    pinMode(green_led_tilt_, OUTPUT);
    pinMode(red_led_tilt_, OUTPUT);
    pinMode(green_led_magnetometer_, OUTPUT);
    pinMode(red_led_magnetometer_, OUTPUT);
}

void Leds::validLocation() const
{
    locationLedRedOff();
    locationLedGreenOn();
}

void Leds::invalidLocation() const
{
    locationLedGreenOff();
    locationLedRedOn();
}

void Leds::tiltOk() const 
{
    tiltLedRedOff();
    tiltLedGreenOn();
} 

void Leds::tiltError() const 
{
    tiltLedGreenOff();
    tiltLedRedOn();
}

void Leds::magnetometerCalibrated() const
{
    magnetometerLedRedOff();
    magnetometerLedGreenOn();
}

void Leds::magnetometerCalibrating() const
{
    magnetometerLedRedOn();
    magnetometerLedGreenOn();
}

void Leds::magnetometerNotCalibrated() const
{
    magnetometerLedRedOn();
    magnetometerLedGreenOff();
}

void Leds::locationLedGreenOff() const
{
    digitalWrite(green_led_location_, LOW);
}

void Leds::locationLedGreenOn() const
{
    digitalWrite(green_led_location_, HIGH);
}

void Leds::locationLedRedOff() const
{
    digitalWrite(red_led_location_, LOW);
}

void Leds::locationLedRedOn() const
{
    digitalWrite(red_led_location_, HIGH);
}

void Leds::tiltLedGreenOff() const
{
    digitalWrite(green_led_tilt_, LOW);
}

void Leds::tiltLedGreenOn() const
{
    digitalWrite(green_led_tilt_, HIGH);
}

void Leds::tiltLedRedOff() const
{
    digitalWrite(red_led_tilt_, LOW);
}

void Leds::tiltLedRedOn() const
{
    digitalWrite(red_led_tilt_, HIGH);
}

void Leds::magnetometerLedGreenOff() const
{
    digitalWrite(green_led_magnetometer_, HIGH);
}

void Leds::magnetometerLedGreenOn() const
{
    digitalWrite(green_led_magnetometer_, LOW);
}

void Leds::magnetometerLedRedOff() const
{
    digitalWrite(red_led_magnetometer_, HIGH);
}

void Leds::magnetometerLedRedOn() const
{
    digitalWrite(red_led_magnetometer_, LOW);
}
