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

#include "scmRTOS.h"
#include "prio_names.h"

const char PROGMEM str_idle[] = "IDLE";
const char PROGMEM str_unknown[] = "???";

const char *get_prio_name(uint_fast8_t prio)
{
    static char name[5];
    if (prio >= OS::PROCESS_COUNT) {
        strcpy_P(name, str_unknown);
    } else {
#if scmRTOS_PRIORITY_ORDER == 1
        prio = OS::PROCESS_COUNT - prio - 1;
#endif
        if (prio == OS::PROCESS_COUNT-1 ) {
            strcpy_P(name, str_idle);
        } else {
            char *p = name;
            *p++ = 'p';
            *p++ = 'r';
            uint8_t tens = '0';
            while (prio >= 10) {
                ++tens;
                prio -= 10;
            }
            if (tens != '0')
                *p++ = tens;
            *p++ = '0'+prio;
            *p = 0;
        }
    }
        
    return name;
}

