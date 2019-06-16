/**
 * Author: sascha_lammers@gmx.de
 */

#pragma once

#define MAINS_FREQUENCY 60.0
#define TIMER1_PRESCALER 64.0

#define TIMER1_TICKS_PER_US            (TIMER1_TICKS_PER_MS / 1000.0)                   // 62.5 / 1000 = 0.0625
#define TIMER1_TICKS_PER_MS            (TIMER1_TICKS_PER_SEC / 1000.0)                  // 62500 / 1000 = 62.5
#define TIMER1_TICKS_PER_SEC           (F_CPU / TIMER1_PRESCALER)                       // 16000000 / 256 = 62500
#define TIMER1_TICKS_PER_HALFWAVE      (TIMER1_TICKS_PER_SEC / (MAINS_FREQUENCY * 2))

#define TIMER1_TICKS_TO_US(ticks)      (ticks / TIMER1_TICKS_PER_US)