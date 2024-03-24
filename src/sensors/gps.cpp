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

#include <sensors/gps.h>
#include <Arduino.h>
#include <SoftwareSerial.h>

using namespace gps;

Gps::Gps (params::GpsParams p):
    rx_pin_(p.rx_pin),
    tx_pin_(p.tx_pin),
    baud_rate_(p.gps_baud)
{

}

void Gps::init()
{
    Serial.println("Initializing GPS");
    serial_ = new SoftwareSerial(rx_pin_, tx_pin_);
    serial_->begin(baud_rate_);
    Serial.println("GPS initialized");
}

void Gps::execute()
{
    while (serial_->available() > 0)
    {
        sensor_.encode(serial_->read());
    }

    if (!sensor_.location.isValid())
    {
        return;
    }

    latlon_ = {sensor_.location.lat(), sensor_.location.lng()};
}

void Gps::log()
{
    if (sensor_.location.isValid())
    {
        Serial.print(sensor_.location.lat(), 6);
        Serial.print(F(","));
        Serial.print(sensor_.location.lng(), 6);
    }
    else
    {
        Serial.print("Invalid location");
    }

    Serial.print(F("  Date/Time: "));
    if (sensor_.date.isValid())
    {
        Serial.print(sensor_.date.month());
        Serial.print(F("/"));
        Serial.print(sensor_.date.day());
        Serial.print(F("/"));
        Serial.print(sensor_.date.year());
    }
    else
    {
        Serial.print(F("Invalid date"));
    }

    Serial.print(F(" "));
    if (sensor_.time.isValid())
    {
        if (sensor_.time.hour() < 10) Serial.print(F("0"));
        Serial.print(sensor_.time.hour());
        Serial.print(F(":"));
        if (sensor_.time.minute() < 10) Serial.print(F("0"));
        Serial.print(sensor_.time.minute());
        Serial.print(F(":"));
        if (sensor_.time.second() < 10) Serial.print(F("0"));
        Serial.print(sensor_.time.second());
        Serial.print(F("."));
        if (sensor_.time.centisecond() < 10) Serial.print(F("0"));
        Serial.print(sensor_.time.centisecond());
    }
    else
    {
        Serial.print(F("INVALID"));
    }

    Serial.println();
}

bool Gps::isLocationValid() const
{
    return latlon_.valid;
}

LatLon Gps::getLocation() const
{
    return latlon_;
}

bool Gps::hasTargetLocation() const
{
    return target_latlon_.valid;
}

void Gps::saveTargetLocation()
{
    target_latlon_ = latlon_;
}

void Gps::setTargetLocation(LatLon latlon)
{
    target_latlon_ = latlon;
}

LatLon Gps::getTargetLocation() const
{
    return target_latlon_;
}
