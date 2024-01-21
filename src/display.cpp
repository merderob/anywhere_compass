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

#include "display.h"
#include <Arduino.h>

Display::Display(params::DisplayParams p):
    green_led_location_(p.green_led_location), 
    red_led_location_(p.red_led_location),
    green_led_tilt_(p.green_led_tilt),
    red_led_tilt_(p.red_led_tilt)
{
};

void Display::init() const
{
    pinMode(red_led_location_, OUTPUT);
    pinMode(green_led_location_, OUTPUT);
}

void Display::displayValidLocation() const
{
    locationLedRedOff();
    locationLedGreenOn();
}

void Display::displayInvalidLocation() const
{
    locationLedGreenOff();
    locationLedRedOn();
}

void Display::displayTiltOk() const 
{
    tiltLedRedOff();
    tiltLedGreenOn();
} 

void Display::displayTiltError() const 
{
    tiltLedGreenOff();
    tiltLedRedOn();
}

void Display::locationLedGreenOff() const
{
    digitalWrite(green_led_location_, LOW);
}

void Display::locationLedGreenOn() const
{
    digitalWrite(green_led_location_, HIGH);
}

void Display::locationLedRedOff() const
{
    digitalWrite(red_led_location_, LOW);
}

void Display::locationLedRedOn() const
{
    digitalWrite(red_led_location_, HIGH);
}

void Display::tiltLedGreenOff() const
{
    digitalWrite(green_led_tilt_, LOW);
}

void Display::tiltLedGreenOn() const
{
    digitalWrite(green_led_tilt_, HIGH);
}

void Display::tiltLedRedOff() const
{
    digitalWrite(red_led_tilt_, LOW);
}

void Display::tiltLedRedOn() const
{
    digitalWrite(red_led_tilt_, HIGH);
}
