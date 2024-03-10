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

namespace gps
{
    struct LatLon 
    {
        LatLon():lat(0.0), lon(0.0), valid(false){};
        LatLon(double la, double lo):lat(la), lon(lo), valid(true){}; 
        double lat = 0.0;
        double lon = 0.0;
        bool valid = false; 
    };
} 

namespace compass
{
    struct Calibration
    {
        Calibration():x_offset(0.0f), y_offset(0.0f), z_offset(0.0f), x_scale(1.0f), y_scale(1.0f), z_scale(1.0f){};
        Calibration(float x_o, float y_o, float z_o, float x_s, float y_s, float z_s):
            x_offset(x_o), y_offset(y_o), z_offset(z_o), x_scale(x_s), y_scale(y_s), z_scale(z_s){};

        float x_offset = 0.0f;
        float y_offset = 0.0f;
        float z_offset = 0.0f;
        float x_scale = 1.0f;
        float y_scale = 1.0f;
        float z_scale = 1.0f;
    };   
}
