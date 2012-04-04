scmRTOS Cortex-M3/GCC port, LPC17XX samples

Samples directory structure:

1-EventFlag    - OS::TEventFlag sample.
2-Message      - OS::TMessage sample       (coming soon)
3-Channel      - OS::channel<> sample      (coming soon)
4-Debug        - scmRTOS debug capabilities sample 
SamplesCommon  - Common files for all samples.
               NXP subdirectory contains only files from lpc17xx.cmsis.driver.library
               that required by samples.
               The files are changed - parentheses added to some macro arguments.
scmRTOS        - scmRTOS Common, Extensions and Cortex-M3/GCC port files.
 
Run switch.bat (in Windows) or switch.sh (in Linux) to obtain scmRTOS files.

Run make in sample directory for project compilation.

