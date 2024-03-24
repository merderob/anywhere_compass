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

/// @brief Class representing a button input with analog value.
class AnalogButton
{
public:
    /// @brief Constructor.
    AnalogButton(int pin, int nominal_value, int threshold);
    /// @brief Reads the analog value of the input pin.
    void read();
    /// @brief Returns true if the button is pressed (the value is in the threshold).
    /// @return True, if the button is pressed.
    bool isPressed() const;
    /// @brief Returns true if the button was pressed  in the previous cycle (the value was in the threshold).
    /// @return True, if the button was pressed.
    bool wasPressed() const;
private:
    /// @brief The input analog pin.
    int pin_ = 0;
    /// @brief The nominal value of the analog input.
    int nominal_value_ = 0;
    /// @brief The threshold in which the input value is accepted.
    int threshold_ = 0;
    /// @brief Stores if the input is valid.
    bool is_pressed_ = false;
    /// @brief Stores if the input in the previous execution was valid.
    bool was_pressed_ = false;
};
