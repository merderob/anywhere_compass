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
#include "imu.h"
#include "compass.h"
#include "gps.h"
#include "user_input.h"

 // the number of the pushbutton pin
const int button_pin = 2; 
// variable for reading the pushbutton status
int button_state = 0;  
unsigned long prev_exec_time_ms = 0;

Display display;

Imu imu;

Compass compass;

Gps gps;

UserInput user_input;

void setup()
{
    Serial.begin(params::DebugParams::serial_baud_rate);

    pinMode(button_pin, INPUT);
    imu.init();
    compass.init();
    gps.init();
    display.init();
}

void loop()
{
    const auto cur_exec_time_ms = millis();
    if (cur_exec_time_ms - prev_exec_time_ms > 100)
    {
        // read the state of the pushbutton value:
        button_state = digitalRead(button_pin);
        // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
        if (button_state == HIGH) 
        {
            // Todo save location
        }

        imu.execute();
        if (imu.checkTilt())
        {
            display.displayTiltOk();
        }
        else
        {
            display.displayTiltError();
        }
        
        gps.execute();
        if (gps.isLocationValid())
        {
            display.displayValidLocation();
        }
        else
        {
            display.displayInvalidLocation();
        }
    }
}
