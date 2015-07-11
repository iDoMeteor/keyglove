// Keyglove controller source code - Feedback implementations for vibration motor
// 2015-07-03 by Jeff Rowberg <jeff@rowberg.net>

/* ============================================
Controller code is placed under the MIT license
Copyright (c) 2015 Jeff Rowberg

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
===============================================
*/

/**
 * @file support_feedback_vibrate.cpp
 * @brief Feedback implementations for vibration motor
 * @author Jeff Rowberg
 * @date 2015-07-03
 *
 * This file defines the feeback functionality for the vibration motor that may
 * be included as an optional module in a Keyglove modular hardware design. This
 * file is meant to contain only behavioral logic and abstracted functions that
 * do not require specific pin knowledge of the selected MCU. Any pins used
 * should be defined in the selected MCU board support file.
 *
 * Normally it is not necessary to edit this file.
 */

#include "keyglove.h"
#include "support_board.h"
#include "support_protocol.h"
#include "support_feedback.h"
#include "support_feedback_vibrate.h"

feedback_vibrate_mode_t feedbackVibrateMode;    ///< Vibration mode
uint16_t feedbackVibrateTick;                   ///< Vibration tick reference
uint16_t feedbackVibrateDuration;               ///< Vibration pattern duration

/**
 * @brief Sets vibration motor control pin logic state
 * @param[in] logic Zero for low (off), non-zero for high (on)
 * @see KG_PIN_VIBRATE
 */
void feedback_set_vibrate_logic(uint8_t logic) {
    digitalWrite(KG_PIN_VIBRATE, logic == 0 ? HIGH : LOW); // NOTE: active low logic control
}

/**
 * @brief Sets the operational mode of the vibration motor
 * @param[in] mode Vibration mode to use
 * @param[in] duration Duration in 10ms units to run pattern before ending (0 to run forever)
 */
void feedback_set_vibrate_mode(feedback_vibrate_mode_t mode, uint8_t duration) {
    feedbackVibrateMode = mode;
    if (mode == KG_VIBRATE_MODE_OFF) feedback_set_vibrate_logic(0);
    else if (mode == KG_VIBRATE_MODE_SOLID) feedback_set_vibrate_logic(1);
    feedbackVibrateTick = 0xFFFF;
    feedbackVibrateDuration = duration;
}

/**
 * @brief Initialize vibration feedback subsystem
 */
void setup_feedback_vibrate() {
    pinMode(KG_PIN_VIBRATE, OUTPUT);
    digitalWrite(KG_PIN_VIBRATE, HIGH); // transistor switch makes it active-low

    // SELF-TEST
    //feedback_set_vibrate_mode(KG_VIBRATE_MODE_TINYBUZZ, 20);
}

/**
 * @brief Update status of vibration feedback subystem, called at 100Hz from loop()
 */
void update_feedback_vibrate() {
     if (feedbackVibrateMode > 0) {
         if      (feedbackVibrateMode == KG_VIBRATE_MODE_LONGBUZZ   && feedbackVibrateTick % 50 == 0) feedback_set_vibrate_logic(feedbackVibrateTick % 100 >= 50 ? 0 : 1);
         else if (feedbackVibrateMode == KG_VIBRATE_MODE_LONGPULSE  && feedbackVibrateTick % 25 == 0) feedback_set_vibrate_logic(feedbackVibrateTick % 100 >= 25 ? 0 : 1);
         else if (feedbackVibrateMode == KG_VIBRATE_MODE_SHORTBUZZ  && feedbackVibrateTick % 10 == 0) feedback_set_vibrate_logic(feedbackVibrateTick %  20 >= 10 ? 0 : 1);
         else if (feedbackVibrateMode == KG_VIBRATE_MODE_SHORTPULSE && feedbackVibrateTick %  5 == 0) feedback_set_vibrate_logic(feedbackVibrateTick %  20 >=  5 ? 0 : 1);
         else if (feedbackVibrateMode == KG_VIBRATE_MODE_TINYBUZZ   && feedbackVibrateTick %  5 == 0) feedback_set_vibrate_logic(feedbackVibrateTick %  10 >=  5 ? 0 : 1);
         if (++feedbackVibrateTick >= feedbackVibrateDuration && feedbackVibrateDuration > 0) feedback_set_vibrate_mode(KG_VIBRATE_MODE_OFF, 0);
     }
}
