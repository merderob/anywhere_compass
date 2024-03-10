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

#include "sensors/compass.h"

using namespace compass;

Compass::Compass(params::CompassParams p)
{
    sensor_.setMagneticDeclination(p.magnetic_declination_degrees, p.magnetic_declination_minutes);
}

void Compass::init()
{
    Serial.println("Initializing compass");
    sensor_.init();
    Serial.println("Initialized compass");
}

void Compass::execute()
{
    const auto prev_state = state_;
    switch (state_)
    {
    case State::UNCALIBRATED:
        break;
    case State::CALIBRATION_REQUESTED:
        state_ = State::CALIBRATING;
        break;
    case State::CALIBRATING:
        Serial.println("Clearing compass calibration.");
        sensor_.clearCalibration();
        Serial.println("Calibrating compass...");
        sensor_.calibrate();
        Serial.println("Calibration done.");
        state_ = State::CALIBRATED;
        break;
    case State::CALIBRATED:
        sensor_.read();
        azimuth_deg_ = sensor_.getAzimuth();
        break;
    }
    can_save_calibration_ = (prev_state == State::CALIBRATING) && (state_ == State::CALIBRATED);
}

void Compass::log()
{
    Serial.print("az: ");
    Serial.print(azimuth_deg_);
    Serial.println();
}

void Compass::requestCalibration()
{
    state_ = State::CALIBRATION_REQUESTED;
}

bool Compass::calibrated() const
{
    return state_ == State::CALIBRATED;
}

void Compass::setCalibration(const compass::Calibration& calibration)
{
    sensor_.setCalibrationOffsets(calibration.x_offset, calibration.y_offset, calibration.z_offset);
    sensor_.setCalibrationScales(calibration.x_scale, calibration.y_scale, calibration.z_scale);
    state_ = State::CALIBRATED;
}

Calibration Compass::getCalibration()
{
    return {
        sensor_.getCalibrationOffset(0),
        sensor_.getCalibrationOffset(1),
        sensor_.getCalibrationOffset(2),
        sensor_.getCalibrationScale(0),
        sensor_.getCalibrationScale(1),
        sensor_.getCalibrationScale(2)
    };
}

Compass::State Compass::getState() const
{
    return state_;
}

int Compass::getAzimuith() const
{
    return azimuth_deg_;
}

bool Compass::canSaveCalibration() const
{
    return can_save_calibration_;
}
