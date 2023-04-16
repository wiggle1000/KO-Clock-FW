/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <stdio.h>
#include <cmath>
#include "pico/stdlib.h"
#include "hardware/adc.h"

#define NUM_GATE_OUTS 6
#define NUM_LEDS 3

#define GPIO_CLK 0
#define GPIO_RST 1
#define GPIO_PLAY 14

#define GPIO_ADC 26

#define GPIO_TMULT_A 15
#define GPIO_TMULT_B 10


enum LEDState
{
    SOLID_ON,
    SOLID_OFF,
    SOLID_HALF,
    BLINK_SLOW,
    BLINK_MED,
    BLINK_FAST,
    FADE_SLOW,
    FADE_MED,
    FADE_FAST,
};

/// @brief Gate LEDs arent here, they're hardwired to the gate outs
enum PanelLED
{
    Reset,
    Clock,
    PlayButton
};

class IOHelper
{
    private:
        const uint8_t GATE_IO_PINS[NUM_GATE_OUTS] = {4, 5, 6, 7, 8, 9};
        const uint8_t LED_IO_PINS[NUM_LEDS] = {2, 3, 16};
        const uint8_t MUX_ADDR_PINS[3] = {11, 12, 13};

        bool WAS_PLAY  = false;
        bool WAS_CLK   = false;
        bool WAS_RST   = false;
        uint8_t LAST_TM_SWITCH    = 0;

        int16_t ReadADC(uint8_t addr);
        int16_t GetCalibratedValue(uint16_t adcValue, uint16_t zero, uint16_t five);
    public:
        uint16_t LEDCycle = 0;

        /// @brief RESET, CLOCK, PLAY
        LEDState OUT_LEDS[NUM_LEDS];
        
        /// @brief 1, 1/2, 1/4, 1/16, UD, UD/2
        bool OUT_GATES[NUM_GATE_OUTS];
        int16_t CV_UD           = 0;
        int16_t CV_scrub        = 0;
        int16_t CV_timeMult     = 0;
        int16_t CV_swing        = 0;

        bool    IN_PLAY_BTN     = false;
        uint8_t IN_UD_INDEX     = 0;
        int16_t IN_BPM_KNOB     = 0;
        int16_t IN_SWING_KNOB   = 0;
        uint8_t IN_TMULT_SWITCH = 0;

        bool FLAG_PLAY  = false;
        bool FLAG_CLK   = false;
        bool FLAG_RST   = false;

        bool FLAG_TMULT = false;
        

        void Init();
        void ReadFastInputs(long dt);
        void ReadSlowInputs(long dt);
        void WriteOutputs(long dt);

        bool ProcessResetFlag();
        bool ProcessClockFlag();
        bool ProcessPlayFlag();

        void SetLEDState(PanelLED led, LEDState state);
};