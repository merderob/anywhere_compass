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

#include <TinyGPSPlus.h>
#include "sensor_base.h"

class SoftwareSerial;

class Gps: public SensorBase
{
public:
    struct LatLon 
    {
        LatLon():lat(0.0), lon(0.0){};
        LatLon(double la, double lo):lat(la), lon(lo){}; 
        double lat = 0.0;
        double lon = 0.0;
    };

    /// @brief Constructor.
    /// @param p The GPS parameters.
    Gps(params::GpsParams p = {});

    void init() override;
    void execute() override;
    void log() override;

    bool isLocationValid() const;
    LatLon getLatLon() const;

private:
    TinyGPSPlus sensor_;
    // The serial connection to the GPS device
    SoftwareSerial* serial_ = nullptr;

    int rx_pin_ = 0;
    int tx_pin_ = 0;
    long baud_rate_ = 9600;

    LatLon latlon_;
};
