/**
 * Author: sascha_lammers@gmx.de
 */

#pragma once

#if DEBUG_STATISTICS

// number of cycles to cover
#define DEBUG_STATISTICS_COUNT                      10

class DebugStatistics {
public:
    typedef struct {
        uint32_t timeMs;
        uint32_t cycleCounter;
        uint16_t startTicks;
        uint16_t endTicks;
        uint16_t nextTicks;
        uint16_t channelTicks[DIMMER_CHANNELS];
    } DebugStats_t;

public:
    DebugStatistics() = default;

    void _overflow();
    uint16_t getOverflowCounter() const;
    uint32_t getTicks() const {
        return getOverflowCounter() * (1UL << 16);
    }

    void addFrame();
    DebugStats_t &getFrame();

    void print(Print &output);

private:
    DebugStats_t _stats[DEBUG_STATISTICS_COUNT];

    volatile uint16_t _overflowCounter;
    volatile uint8_t _frameCounter;
};

extern DebugStatistics debugStats;

#define DebugStats_addFrame()                           debugStats.addFrame();

#else

#define DebugStats_addFrame()                           ;

#endif
