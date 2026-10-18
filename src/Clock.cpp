#include "Clock.h"

#if defined(__AVR__) && defined(TIMER1_OVF_vect) && (F_CPU == 16000000UL)

namespace {

// 16 MHz / 64 = 250 kHz -> 250 ticks per millisecond; Timer1 overflows every 65536 ticks.
const uint32_t TICKS_PER_MS = 250;

volatile uint32_t overflows = 0;

}  // namespace

ISR(TIMER1_OVF_vect) {
  overflows++;
}

namespace showclock {

void begin() {
  uint8_t sreg = SREG;
  cli();
  TCCR1A = 0;                        // normal counting mode
  TCCR1B = _BV(CS11) | _BV(CS10);    // clock / 64
  TCNT1 = 0;
  TIFR1 = _BV(TOV1);                 // clear any pending overflow
  TIMSK1 = _BV(TOIE1);
  overflows = 0;
  SREG = sreg;
}

uint32_t nowMs() {
  uint8_t sreg = SREG;
  cli();
  uint32_t ovf = overflows;
  uint16_t ticks = TCNT1;
  // An overflow that has happened but whose interrupt has not run yet (interrupts were
  // off, e.g. during FastLED.show()) still has to be counted.
  if ((TIFR1 & _BV(TOV1)) && ticks < 0x8000) ovf++;
  SREG = sreg;

  uint64_t total = (static_cast<uint64_t>(ovf) << 16) | ticks;
  return static_cast<uint32_t>(total / TICKS_PER_MS);
}

}  // namespace showclock

#else  // other boards: no FastLED-safe timer available, use millis()

namespace showclock {

void begin() {}
uint32_t nowMs() { return millis(); }

}  // namespace showclock

#endif
