/**
 * Author: sascha_lammers@gmx.de
 */

#include "main.h"

#if DEBUG_STATISTICS

static void dimmer_stats_bubble_sort(DebugStatistics::DebugStats_t frames[])
{
    constexpr uint8_t count = DEBUG_STATISTICS_COUNT - 1;
    uint8_t i, j;
    for (i = 0; i < count; i++) {
        for (j = 0; j < count - i; j++)   {
            if (frames[j].cycleCounter > frames[j + 1].cycleCounter) {
                swap<DebugStatistics::DebugStats_t>(frames[j], frames[j + 1]);
            }
        }
    }
}

DebugStatistics debugStats;

void DebugStatistics::_overflow()
{
    _overflowCounter++;
}

uint16_t DebugStatistics::getOverflowCounter() const
{
    uint16_t cnt;
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        cnt = _overflowCounter;
        if (dimmer._isOvfPending()) {
            cnt++;
        }
    }
    return cnt;
}

void DebugStatistics::addFrame()
{
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        auto &frame = _stats[_frameCounter];
        frame = {};
        frame.cycleCounter = _stats[(_frameCounter + DEBUG_STATISTICS_COUNT - 1) % DEBUG_STATISTICS_COUNT].cycleCounter + 1;
        frame.timeMs = millis();
        frame.startTicks = OCR1A;

        if (++_frameCounter >= DEBUG_STATISTICS_COUNT) {
            _frameCounter = 0;
        }
        sei();
    }
}

DebugStatistics::DebugStats_t &DebugStatistics::getFrame()
{
    return _stats[_frameCounter - 1];
}

void DebugStatistics::print(Print &output)
{
    DebugStats_t _statsTmp[DEBUG_STATISTICS_COUNT];
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        memcpy(_statsTmp, _stats, sizeof(_statsTmp));
    }
    dimmer_stats_bubble_sort(_statsTmp);
    //                    012345012345670123456012345601234560123456012345601234560123456
    Serial_printf_P(PSTR("cycle time    start  end    next   ch0    ch1    ch2    ch3    \n"));
    for(uint8_t i = 0; i < DEBUG_STATISTICS_COUNT; i++) {
        auto &frame = _statsTmp[i];
        if (frame.cycleCounter) {
            Serial_printf_P(PSTR("%-5u %-7lu %-6u %-6u %-6u %-6u %-6u %-6u %-6u\n"),
                (uint16_t)frame.cycleCounter, frame.timeMs, frame.startTicks, frame.endTicks, frame.nextTicks,
                frame.channelTicks[0], frame.channelTicks[1], frame.channelTicks[2], frame.channelTicks[3]
            );
        }
    }
}

#endif
