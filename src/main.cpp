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

#include "user_input.h"
#include "sensor_handle.h"
#include "display.h"

unsigned long prev_exec_time_ms = 0;
unsigned long exec_time_ms = 100; 

SensorHandle sensors;

Display display {sensors};

UserInput user_input {sensors};


void setup()
{
    Serial.begin(params::DebugParams::serial_baud_rate);
    user_input.init();
    sensors.init();
    display.init();
}

void loop()
{
    const auto cur_exec_time_ms = millis();
    if (cur_exec_time_ms - prev_exec_time_ms > exec_time_ms)
    {
        user_input.execute();
        sensors.execute();
        display.execute();
        prev_exec_time_ms = cur_exec_time_ms;
    }
}
