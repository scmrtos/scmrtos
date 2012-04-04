#ifndef HARDWARE_H__
#define HARDWARE_H__
//---------------------------------------------------------------------------
//
//      Clock settings, RTOS timings
//

#define SLCK            32768L      // something about :-(
#define MAINCLK         4032000LL
#define PLLMUL      36
#define PLLDIV      3
//#define MAINCLK         18432000LL
//#define PLLMUL          26
//#define PLLDIV          5
#define PLLCLK          ((MAINCLK * PLLMUL) / PLLDIV)
#define MCK             (PLLCLK / 2)
#define PCK             SLCK
#define RTOS_TICK_RATE  2000ULL // Hz

// Time in RTOS timer ticks but not less than 1 tick to avoid infinite sleep instead of shortest possible
#define RTOS_MS(x)  (((x) * RTOS_TICK_RATE / 1000) ? ((x) * RTOS_TICK_RATE / 1000) : 1)

#endif  // HARDWARE_H__
