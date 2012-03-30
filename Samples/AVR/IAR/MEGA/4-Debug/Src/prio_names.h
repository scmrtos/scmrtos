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

//  returns priority name string or "???" if prio >= OS::PROCESS_COUNT
const char *get_prio_name(uint_fast8_t prio);

#endif  // PRIO_NAMES_H

