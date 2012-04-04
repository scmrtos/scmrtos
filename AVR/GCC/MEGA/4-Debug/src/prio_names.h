//-----------------------------------------------------------------------------
//
//      scmRTOS port test/sample project
//
//      Sample '4-Debug'
//      scmRTOS priority to string converter
//
//      $Revision$
//      $Date::             $
//

#ifndef PRIO_NAMES_H
#define PRIO_NAMES_H

#include <avr/pgmspace.h>

//-----------------------------------------------------------------------------
// Avoid avr-g++ bug -- placing prog_char into .rodata and dummy warning
// 'only initialized variables can be placed into program memory area'
// for PROGMEM variables

#undef PROGMEM
#define PROGMEM __attribute__((__section__(".progmem.data")))

#undef  PSTR
#define PSTR(s) (__extension__({static const char __c[] PROGMEM = (s); &__c[0];}))

//  returns priority name string or "???" if prio >= OS::PROCESS_COUNT
const char *get_prio_name(uint_fast8_t prio);

#endif  // PRIO_NAMES_H

