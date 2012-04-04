AVR/IAR scmRTOS port samples -- short description.

The samples are intended for all non-xmega AVRs including 90USB, 90CAN, 90PWM families
and even for tinyAVRs with enough SRAM.

Samples directory structure:

1-EventFlag    - OS::TEventFlag sample.
2-Message      - OS::TMessage sample.
3-Channel      - OS::channel<> sample.
                 Also the sample shows how to use scmRTOS v3.xx oriented
                 sources with scmRTOS v4.00
4-Debug        - scmRTOS debug capabilities sample.
SamplesCommon  - Common files for all samples.
scmRTOS        - scmRTOS Common, Extensions and AVR/IAR port files.
 
Run switch.bat to obtain scmRTOS files.
Add "^/branches/pre-v400" argument to switch.bat if pre-v400 branch still not merged with trunk.

Read more:

AVR/IAR Release description (in English)
    http://scmrtos.sourceforge.net/AVR_IAR_Release

1-EventFlag sample detailed explanation (in Ukrainian, Russian and English)
    http://real.kiev.ua/scmrtos/1-eventflag/

