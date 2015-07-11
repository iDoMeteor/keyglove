// Keyglove controller source code - Feedback implementations for piezo buzzer
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
 * @file support_feedback_piezo.cpp
 * @brief Feedback implementations for piezo buzzer
 * @author Jeff Rowberg
 * @date 2015-07-03
 *
 * This file defines the feeback functionality for the piezo buzzer that may be
 * included as an optional module in a Keyglove modular hardware design. This
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
#include "support_feedback_piezo.h"

feedback_piezo_mode_t feedbackPiezoMode;    ///< Piezo sound mode
uint16_t feedbackPiezoTick;                 ///< Piezo tick reference
uint16_t feedbackPiezoDuration;             ///< Piezo pattern duration
uint16_t feedbackPiezoFrequency;            ///< Piezo frequency to use for tone generation

/**
 * @brief Enables or disables the piezo buzzer using a certain frequency
 * @param[in] frequency Frequency (Hz) of tone to generate, or zero to disable
 * @see KG_PIN_PIEZO
 */
void feedback_set_piezo_tone(uint16_t frequency) {
    if (frequency == 0) {
        noTone(KG_PIN_PIEZO);
    } else {
        tone(KG_PIN_PIEZO, frequency);
    }
}

/**
 * @brief Sets the operational mode of the piezo buzzer
 * @param[in] mode Piezo mode to use
 * @param[in] duration Duration in 10ms units to run pattern before ending (0 to run forever)
 * @param[in] frequency Frequency (Hz) of tone to generate
 */
void feedback_set_piezo_mode(feedback_piezo_mode_t mode, uint8_t duration, uint16_t frequency) {
    feedbackPiezoMode = mode;
    feedbackPiezoFrequency = frequency;
    if (mode == KG_PIEZO_MODE_OFF) feedback_set_piezo_tone(0);
    else if (mode == KG_PIEZO_MODE_SOLID) feedback_set_piezo_tone(frequency);
    feedbackPiezoTick = 0xFFFF;
    feedbackPiezoDuration = duration;
}

/**
 * @brief Initialize piezo feedback subsystem
 */
void setup_feedback_piezo() {
    pinMode(KG_PIN_PIEZO, OUTPUT);
    digitalWrite(KG_PIN_PIEZO, LOW);
    noTone(KG_PIN_PIEZO);

    // SELF-TEST
    //feedback_set_piezo_mode(KG_PIEZO_TINYPULSE, 20);
}

/**
 * @brief Update status of piezo feedback subystem, called at 100Hz from loop()
 */
void update_feedback_piezo() {
     if (feedbackPiezoMode > 0) {
         if      (feedbackPiezoMode == KG_PIEZO_MODE_LONGBEEP   && feedbackPiezoTick % 50 == 0) { feedback_set_piezo_tone(feedbackPiezoTick % 100 >= 50 ? 0 : feedbackPiezoFrequency); }
         else if (feedbackPiezoMode == KG_PIEZO_MODE_LONGPULSE  && feedbackPiezoTick % 25 == 0) { feedback_set_piezo_tone(feedbackPiezoTick % 100 >= 25 ? 0 : feedbackPiezoFrequency); }
         else if (feedbackPiezoMode == KG_PIEZO_MODE_SHORTBEEP  && feedbackPiezoTick % 10 == 0) { feedback_set_piezo_tone(feedbackPiezoTick %  20 >= 10 ? 0 : feedbackPiezoFrequency); }
         else if (feedbackPiezoMode == KG_PIEZO_MODE_SHORTPULSE && feedbackPiezoTick %  5 == 0) { feedback_set_piezo_tone(feedbackPiezoTick %  20 >=  5 ? 0 : feedbackPiezoFrequency); }
         else if (feedbackPiezoMode == KG_PIEZO_MODE_TINYBEEP   && feedbackPiezoTick %  5 == 0) { feedback_set_piezo_tone(feedbackPiezoTick %  10 >=  5 ? 0 : feedbackPiezoFrequency); }
         else if (feedbackPiezoMode == KG_PIEZO_MODE_TINYPULSE  && feedbackPiezoTick %  2 == 0) { feedback_set_piezo_tone(feedbackPiezoTick %  10 >=  2 ? 0 : feedbackPiezoFrequency); }
         if (++feedbackPiezoTick >= feedbackPiezoDuration && feedbackPiezoDuration > 0) feedback_set_piezo_mode(KG_PIEZO_MODE_OFF, 0, 0);
     }
}
