/* THIS SAMPLE CODE IS PROVIDED AS IS AND IS SUBJECT TO ALTERATIONS. FUJITSU */
/* MICROELECTRONICS ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR */
/* ELIGIBILITY FOR ANY PURPOSES.                                             */
/*                 (C) Fujitsu Microelectronics Europe GmbH                  */
;==============================================================================
; 1  Contents
;==============================================================================
; 1       Contents
; 2       Disclaimer
;
; 3       History
;
; 4       Settings
; 4.1     Controller Family
; 4.1.1   Flash wait cycles
; 4.2     Stack Type and Stack Size
; 4.3     Low-Level Library Interface
; 4.4     C++ start-up 
; 4.5     Clock Selection
; 4.5.1   Select clock source  
; 4.5.2   Select PLL ratio  
; 4.5.3   Select CPU and peripheral and external-bus clock divider  
; 4.5.4   Select CAN clock 
; 4.5.5   Select Clock Modulator  
; 4.6     External Bus Interface
; 4.6.1   Select Chip mode
; 4.6.2   Select Chipselect
; 4.6.3   Set memory addressing for Chipselects
; 4.6.4   Configure Chipselect Area
; 4.6.5   Set Wait cycles for Chipselects
; 4.6.6   Select External bus mode (Address lines 23:16)
; 4.6.7   Select External bus mode (Control signals)
;
; 5       Section and Data Declaration
; 5.1     Define Stack Size
; 5.2     Define Sections
;
; 6.      S T A R T 
; 6.1     Clock startup
; 6.1.1   Set PLL Multiplier
; 6.1.2   Start PLLs 
; 6.1.3   Wait for PLL oscillation stabilisation
; 6.1.4   Set Clocks 
; 6.1.4.1 Set CPU and Peripheral and External Bus Clock Divider
; 6.1.4.2 Set External Bus Interface Clock
; 6.1.4.3 Set CAN Clock Prescaler
; 6.1.4.4 Switch Main Clock Mode
; 6.1.4.5 Switch Subclock Mode
; 6.1.4.6 Switch to PLL Mode
; 6.2     Set BusInterface
; 6.2.1   Set CS0 
; 6.2.2   Set CS1 
; 6.2.3   Set CS2  
; 6.2.4   Set CS3
; 6.2.5   set Port Function Register
; 6.2.6   Enable used CS
; 6.2.7   Set Flash wait cycles
; 6.3     Initialise Stack Pointer and Table Base register
; 6.4     Clear data 
; 6.5     Copy Init Section from ROM to RAM
; 6.6     C Library Initialization
; 6.7     Call C++ Constructors
; 6.8     Call Main Routine
; 6.9     Return from Main Function
;==============================================================================
; 2  Disclaimer
;==============================================================================
;                   Fujitsu Microelectronics Europe GmbH                       
;                 http://emea.fujitsu.com/microelectronics 
;                                                            
; The following  software  is for  demonstration  purposes only.  It is not
; fully  tested, nor validated  in order  to fullfill  its task  under  all
; circumstances.  Therefore,  this software or  any part of it must only be
; used in an evaluation laboratory environment.                        
; This software is subject to the rules of our standard DISCLAIMER, that is
; delivered with our  SW-tools on the Fujitsu Microcontrollers CD 
; (V3.4 or higher "\START.HTM") or on our Internet Pages:
; http://www.fme.gsdc.de/gsdc.htm
; http://emea.fujitsu.com/microelectronics 
;
;==============================================================================
; 3  History
;==============================================================================
;
;==============================================================================
;       MB9127x Series C Compiler's 
;
;       Startup file for memory and basic controller initialisation
;==============================================================================
;History:
;
; 2005-08-04 V1.0 UMa  Release first version
; 2006-12-07 V1.1 MHe  Add FLASH wait cycles setting
;
;==============================================================================
; 4  Settings
;==============================================================================
;
; CHECK ALL OPTIONS WHETHER THEY FIT TO THE APPLICATION;
;
; Configure this startup file in the "Settings" section. Search for
; comments with leading "; <<<". This points to the items to be set.
;==============================================================================
;
#set    OFF             0
#set    ON              1
#set    LOW_PRIOR       31
;
;==============================================================================
; 4.1  Controller Family
;==============================================================================
#set    MB91V280        0                       ; FR-60Lite, MB91V280 series
#set    MB91F272        1                       ; FR-60Lite, MB91F272 series
;
#set    FAMILY          MB91F272                ; <<< select family

;====================================================================
; 4.1.1  Flash wait cycles
;====================================================================
; With this setting the number of wait cycles for access to FLASH 
; memory is set. 


#set   FLASH_READ_ONLY   ON      ; <<< setting Flash-mode


 
; ON:  For read-only applications 1 wait cycle is set which allows 
;      to read at maximum speed. Up to 33 MHz can be operated. 
       
; OFF: For read-and-write applications 3 wait cycles are set. 
;      Up to 33 MHz can be operated.
      
  
; Note: Please check also the 91265-series HW-manual chapter "Flash memory"

;==============================================================================
; 4.2  Stack Type and Stack Size
;==============================================================================
;
#set    USRSTACK        0                       ; user stack: for main program
#set    SYSSTACK        1                       ; system stack: for main program and interrupts
;
#set    STACKUSE        SYSSTACK                ; <<< set active stack
;
#set    STACK_RESERVE   ON                      ; <<< reserve stack area in this module
#set    STACK_SYS_SIZE  0x400-4                 ; <<< byte size of System stack
#set    STACK_USR_SIZE  2                       ; <<< byte size of User stack 
;
; - If the active stack is set to SYSSTACK, it is used for main program
;   and interrupts. In this case, the user stack could be set to a dummy
;   size.
;   If the active stack is set to user stack, it is used for the main
;   program but the system stack is automatically activated, if an inter-
;   rupt is serviced. Both stack areas must have a reasonable size.
; - If STACK_RESERVE is ON, the sections USTACK and SSTACK are reserved 
;   in this module. Otherwise, they have to be reserved in other modules.
;   If STACK_RESERVE is OFF, the size definitions STACK_SYS_SIZE and 
;   STACK_USR_SIZE have no meaning.
; - Even if they are reserved in other modules, they are still initialised
;   in this start-up file.
;
; - If only system stack is used and SSB is linked to a different bank
;   than USB, make sure that all C-modules (which generate far pointers 
;   to stack data) have "#pragma SSB". Applies only to exclusive confi-
;   gurations.
; - Note, several library functions require quite a big stack (due to 
;   ANSI). Check the stack information files (*.stk) in the LIB\911
;   directory.
;==============================================================================
; 4.3  Low-Level Library Interface
;==============================================================================
#set    CLIBINIT        OFF                     ; <<< select extended library usage

; This option has only to be set, if stream-IO/standard-IO function of
; the C-library have to be used (printf(), fopen()...). This also 
; requires low-level functions to be defined by the application 
; software.
; For other library functions (like e.g. sprintf()) all this is not
; necessary. However, several functions consume a large amount of stack.
;==============================================================================
; 4.4  C++ start-up 
;==============================================================================
#set    CPLUSPLUS       ON                     ; <<< activate if c++ files are used
;
; In the C++ specifications, when external or static objects are used, 
; a constructor must be called followed by the main function.  
; Because four-byte pointers to the main function are stored in the 
; EXT_CTOR_DTOR section, call a constructor sequentially from the 
; lower address of the four addresses in that section.
;
; If using C++ sources, activate this function to create the section
; EXT_CTOR_DTOR. 
;==============================================================================
; 4.5  Clock Selection
;==============================================================================
; There exist 3 internal clock trees.
; CPU clock, peripheral clock and external bus clock
; There is also the possibility to select a specific clock for the CAN Controller
; As first step the internal frequency (PLL, use or not) must be selected.
; Afterwards the 3 clock trees and the CAN Controller must be set-up.
; There is also a clock modulator, intended to minimize the electromagnetic 
; interference - EMI.
;==============================================================================
; 4.5.1 Select clock source  
;==============================================================================
#set    NOCLOCK         0                       ; do not touch CKSCR register
#set    MAINCLOCK       1                       ; select main clock 
                                                ; (1/2 external)
#set    MAINPLLCLOCK    2                       ; select main clock with PLL
#set    SUBCLOCK        3                       ; select subclock
;
#set    CLOCKSOURCE     MAINPLLCLOCK            ; <<< set clock source
;
#set    ENABLE_SUBCLOCK OFF                     ; <<< set if Subclock exists 
;                                               ;     and should be enabled
;==============================================================================
; 4.5.2 Select PLL ratio  
;==============================================================================
; Select the PLL multiplier. 
; For the maximum permitted frequency, please refer to the hardware manual.
; The frequency in brackets is the resulting frequency for a source oszillation 
; of 4 MHz.
;
#set    PLLx1           0x00                     ; ext. clock/quartz x1 (4 MHz) 
#set    PLLx2           0x01                     ; ext. clock/quartz x2 (8 MHz)
#set    PLLx3           0x02                     ; ext. clock/quartz x3 (12 MHz)
#set    PLLx4           0x03                     ; ext. clock/quartz x4 (16 MHz) 
#set    PLLx5           0x04                     ; ext. clock/quartz x5 (20 MHz) 
#set    PLLx6           0x05                     ; ext. clock/quartz x6 (24 MHz) 
#set    PLLx7           0x06                     ; ext. clock/quartz x7 (28 MHz) 
#set    PLLx8           0x07                     ; ext. clock/quartz x8 (32 MHz) 
;
#set    PLLSPEED        PLLx8                    ; <<< set PLL ratio (base clock)
;
;==============================================================================
; 4.5.3 Select CPU and peripheral and External-bus clock  
;==============================================================================
; Select the divide ratio for the clocks used for internal device operation. 
; Do not set a divide ratio that exceeds the maximum operating frequency of the device.
; For the maximum permitted frequency, please refer to the hardware manual. 
;                    
#set    CLOCK_DIV1      0x00  ; clock = 1/1 source clock
#set    CLOCK_DIV2      0x01  ; clock = 1/2 source clock 
#set    CLOCK_DIV3      0x02  ; clock = 1/3 source clock 
#set    CLOCK_DIV4      0x03  ; clock = 1/4 source clock 
#set    CLOCK_DIV5      0x04  ; clock = 1/5 source clock 
#set    CLOCK_DIV6      0x05  ; clock = 1/6 source clock 
#set    CLOCK_DIV7      0x06  ; clock = 1/7 source clock 
#set    CLOCK_DIV8      0x07  ; clock = 1/8 source clock 
#set    CLOCK_DIV9      0x08  ; clock = 1/9 source clock 
#set    CLOCK_DIV10     0x09  ; clock = 1/10 source clock 
#set    CLOCK_DIV11     0x0A  ; clock = 1/11 source clock 
#set    CLOCK_DIV12     0x0B  ; clock = 1/12 source clock 
#set    CLOCK_DIV13     0x0C  ; clock = 1/13 source clock 
#set    CLOCK_DIV14     0x0D  ; clock = 1/14 source clock 
#set    CLOCK_DIV15     0x0E  ; clock = 1/15 source clock 
#set    CLOCK_DIV16     0x0F  ; clock = 1/16 source clock 
;
;
#set    CPUCLOCK        CLOCK_DIV1              ; <<< set clock divider for CPU clock, CLKB (max. 32 MHz) 
;
#set    PERCLOCK        CLOCK_DIV1              ; <<< set clock divider for CLKP (max. 32 MHz)     
;
#set    EXTBUSCLOCK     CLOCK_DIV2              ; <<< set External bus clock divider (max. 16 MHz)
;
;==============================================================================
; 4.5.4 Select CAN clock 
;==============================================================================
; Select the CAN prescaler clock source and source clock divider
; Do not set a frequency that exceeds the maximum operating frequency of the device.
; For the maximum permitted frequency, please refer to the hardware manual.
;
#set    CANCLOCK        CLOCK_DIV2              ; <<< set prescaler CAN clock divider (max. 16 MHz)
;                                               ;     Divisors 1 to 10 are allowed 
;
;==============================================================================
; 4.6  External Bus Interface
;==============================================================================
; Following set-up the Bus-Interface
;
#set    EXTBUS          OFF                     ; <<< Enable Extern Bus-Interface
;
;
;====================================================================
; 4.6.1  Select Chip mode
;====================================================================
;
; In order to change the chip mode, the mode vecor has to be changed.
; (vectors.c)                                   ; <<< refer to vectors.c
;
;==============================================================================
; 4.6.2  Select Chipselect
;==============================================================================
;
#set    CS0             ON                      ; <<< select Chipselect (ON/OFF)
#set    CS1             OFF                     ; <<< select Chipselect (ON/OFF)
#set    CS2             OFF                     ; <<< select Chipselect (ON/OFF)
#set    CS3             OFF                     ; <<< select Chipselect (ON/OFF)
;
; Select used Chipselects.
; NOTE: Check Hardware Manual which Chipselect signals are available 
; for the used series!
;
#set    CSENABLE        B'00000001              ; <<< enable Chipselects, (1: enabled, 0:disabled)
;                         ||||||||
;                         ||||||||__ CS0 bit, enable/disable CS0 (1/0)
;                         |||||||___ CS1 bit, enable/disable CS1 (1/0)
;                         ||||||____ CS2 bit, enable/disable CS2 (1/0)
;                         |||||_____ CS3 bit, enable/disable CS3 (1/0)
;                         ||||______ -, always 0
;                         |||_______ -, always 0 
;                         ||________ -, always 0
;                         |_________ -, always 0
;==============================================================================
; 4.6.3  Set memory addressing for Chipselects
;==============================================================================
#set    AREASEL0        0x0000                  ; <<< set Starting address for CS0 A[32..16] 
#set    AREASEL1        0x0000                  ; <<< set Starting address for CS1          
#set    AREASEL2        0x0000                  ; <<< set Starting address for CS2
#set    AREASEL3        0x0000                  ; <<< set Starting address for CS3
;
; set starting address of each used Chipselect. Chipselects not used
; (not set to ON in 4.7.2) must not be set (setting ignored).
; NOTE: Just the upper 8-bit must be used A[23-16]
; e.g. when using start address 0x00080000 set 0x0008
;==============================================================================
; 4.6.4  Configure Chipselect Area
;==============================================================================
; Bit description:
; Configure the used Chipselect ACRx register
;
; TYP3 TYP2 TYP1 TYP0    Select access type of each CS
; 0    0    X    X     : Normal access (asynchronous SRAM, I/O, 
;                        single/page/burst-ROM/FLASH) 
; 0    1    X    X     : Address/data multiplexed (8bit or 16bit bus width only)
; 0    X    X    0     : WAIT insertion by RDY disabled
; 0    X    X    1     : WAIT insertion by RDY enabled
; 0    X    0    X     : The WR0X pin to the WR3X pin are used as write strobes 
;                        (WRX is fixed at H-Level)
; 0    X    1    X     : setting not allowed 
; 1    0    0    0     : setting not allowed  
; 1    0    0    1     : setting not allowed 
; 1    0    1    0     : setting not allowed
; 1    0    1    1     : setting not allowed
; 1    1    0    0     : setting not allowed
; 1    1    0    1     : setting not allowed
; 1    1    1    0     : setting not allowed
; 1    1    1    1     : mask area setting
;
;
; WREN: enable or disable write access 
; 1: enabled, 0: disabled     
;
;
; DBW0  : Set data bus width
; 0     : 8-bit (BYTE access) 
; 1     : 16-bit (HALF-WORD access)  
;
;
; ! For chip select 0 and 1 only !
;  ASZ1 ASZ0  :  Select memory size of each chipselect 
;     0    0     :  64 Kbyte (0x01.0000 bytes; use ASR A[23:16] bits) 
;     0    1     : 128 Kbyte (0x02.0000 bytes; use ASR A[23:17] bits)
;     1    0     : 256 Kbyte (0x04.0000 bytes; use ASR A[23:18] bits)
;     1    1     : 512 Kbyte (0x08.0000 bytes; use ASR A[23:19] bits)

; ! For chip select 2 and 3 only !
;  ASZ1 ASZ0  :  Select memory size of each chipselect 
;     0    0     : 1 Mbyte   (0x10.0000 bytes; use ASR A[23:20] bits)
;     0    1     : 2 Mbyte   (0x20.0000 bytes; use ASR A[23:21] bits)
;     1    0     : 4 Mbyte   (0x40.0000 bytes; use ASR A[23:22] bits)
;     1    1     : 8 Mbyte   (0x80.0000 bytes; use ASR A[23] bit)
;
;==============================================================================
#set    CONFIGCS0       B'0011010000000000      ; <<< Configure CS0, ACR register 
#set    CONFIGCS1       B'0000000000000000      ; <<< Configure CS1, ACR register  
#set    CONFIGCS2       B'0000000000000000      ; <<< Configure CS2, ACR register 
#set    CONFIGCS3       B'0000000000000000      ; <<< Configure CS3, ACR register 
;                           || |    | ||||
;                           || |    | ||||__ TYP0 bit, TYP0-4 bits select access type
;                           || |    | |||___ TYP1 bit
;                           || |    | ||____ TYP2 bit
;                           || |    | |_____ TYP3 bit
;                           || |    |_______ WREN bit, enable/disable (1/0) Write access
;                           || |____________ DBW0 bit, DBWx select data bus width
;                           ||______________ ASZ0 bit, ASZx bits select address size of CS
;                           |_______________ ASZ1 bit
;                         
;==============================================================================
; 4.6.5  Set Wait cycles for Chipselects
;==============================================================================
; Bit description:
; set Waitstates for each chipselect area (CSx)
;
; W14  W13  W12   :  First access wait cycle can be set (0-15 cycles)
;  0    0    0    :  0 Wait state
;  0    0    1    :  1 Auto-wait cycle
;  0    1    0    :  2 Auto-wait cycle
; ....
;  1    1    1    :  7 Auto wait cycles
;
; W06  : Read -> Write idle cycle selection
;  0    : 0 cycle
;  1    : 1 cycle
; The read->write cycle is set to prevent a collision between read
; and write data on the data bus when a write cycle follows a read cycle.
;
; W04  : select Write recovery cycle
;  0    : 0 cycle
;  1    : 1 cycle
; The write recovery cycle is set when controlling accesses to a device with
; a restriction on the interval between a write access and the next access.
; 
; W02  : Address -> CSX Delay selection
; 0  : no delay selected
; 1  : delay selected
; When no delay is selected, CS0X to CS7X start being asserted at same time 
; as ASX is asserted. 
;
; W01  : CSX -> RDX/WRX setup extention cycle
; 0    : 0 cycle
; 1    : 1 cycle
; When 0 (0 cycle) is set, RDX/WR0X to WR3X/WRX is output fastest on the rising 
; edge of the external-memory clock MCLK output established immediately after 
; assertion of CSX. WR0X to WR3X/WRX may be delayed by 1 cycle or more depending 
; on the state of the internal bus. When 1 (1 cycle) is set, output of all of 
; RDX/WR0X to WR3X/WRX is always delayed by 1 cycle or more. 
;  
; W00  : RDY/WRX -> CSX hold extension cycle
; 0    : 0 cycle
; 1    : 1 cycle
; When 0 (0 cycle) is set, CS0X to CS3X are negated after the elapse of the  
; hold delay from the rising edge of the external-memory clock MCLK output  
; established after negation of RDX/WR0X to WR3X/WRX. When 1 (1 cycle) is set, 
; CS0X to CS3X are delayed by 1 cycle while being negated.
;==============================================================================
#set    WAITREG0        B'0111000001010011      ; <<< configure CS0 Waitstates, AWR register 
#set    WAITREG1        B'0000000000000000      ; <<< configure CS1 Waitstates, AWR register 
#set    WAITREG2        B'0000000000000000      ; <<< configure CS2 Waitstates, AWR register
#set    WAITREG3        B'0000000000000000      ; <<< configure CS3 Waitstates, AWR register
;                          |||     | | |||
;                          |||     | | |||__ W00 bit, RDY/WRY-> CSX hold cycle
;                          |||     | | ||___ W01 bit, CSX -> RDX/WRX setup extension cycle
;                          |||     | | |____ W02 bit, Address -> CSX Delay selection
;                          |||     | |______ W04 bit, W04/W05 Write recovery cycle 
;                          |||     |________ W06 bit, W06/07 Read -> Write idle cycle 
;                          |||______________ W12 bit, ASZx bits select addressing size 
;                          ||_______________ W13 bit, of CS
;                          |________________ W14 bit
;
;
;==============================================================================
; 4.6.6   Select External bus mode (Address lines 23:16)
;==============================================================================
; Select if the following ports are set to 
; 0: External bus mode, I/O for address lines or
; 1: General purpose port 
; By default these ports are set to External bus mode
;
#set    EPFUNC2         B'00000000              ;<<< select address lines or general purpose port
;                         ||||||||
;                         ||||||||__ A16 
;                         |||||||___ A17 
;                         ||||||____ A18 
;                         |||||_____ A19 
;                         ||||______ A20 
;                         |||_______ A21 
;                         ||________ A22 
;                         |_________ A23 
;
;
#set    EPFUNCE         B'00000000              ;<<< select address lines or general purpose port
;                         ||||||||
;                         ||||||||__ A0 
;                         |||||||___ A1 
;                         ||||||____ A2 
;                         |||||_____ A3 
;                         ||||______ A4 
;                         |||_______ A5 
;                         ||________ A6 
;                         |_________ A7 
;
;
#set    EPFUNCF         B'00000000              ;<<< select address lines or general purpose port
;                         ||||||||
;                         ||||||||__ A8 
;                         |||||||___ A9 
;                         ||||||____ A10 
;                         |||||_____ A11 
;                         ||||______ A12
;                         |||_______ A13
;                         ||________ A14
;                         |_________ A15
;
;
;==============================================================================
; 4.6.7   Select External bus mode (Control signals)
;==============================================================================
; Select if the following ports are set to
; 0: External bus mode, I/O for control signals or
; 1: General purpose port 
; By default these ports are set to External bus mode
;
#set    EPFUNC3         B'00110000              ;<<< select address signals or general purpose port
;                         ||||||||
;                         ||||||||__ ASX 
;                         |||||||___ RDX  
;                         ||||||____ WR0X
;                         |||||_____ WR1X
;                         ||||______ BRQ (91280 only, else always '1') 
;                         |||_______ BGRNTX (91280 only, else always '1') 
;                         ||________ RDY
;                         |_________ SYSCLK 
;
;
#set    EPFUNC9         B'00000000              ;<<< select address signals or general purpose port
;                         ||||||||
;                         ||||||||__ CSX0 
;                         |||||||___ CSX1 
;                         ||||||____ CSX2 
;                         |||||_____ CSX3 
;                         ||||______ -
;                         |||_______ -
;                         ||________ -
;                         |_________ -
;
;==============================================================================
; 5  Section and Data Declaration
;==============================================================================

        .export __start             
        .import _main
        .import _RAM_INIT
        .import _ROM_INIT
        
#if CLIBINIT == ON    
        .export __exit 
        .import _exit
        .import __stream_init
#endif

#if CPLUSPLUS == ON
        .export __abort
        .import ___call_dtors
        .import _atexit
#endif
;==============================================================================
; 5.1 Define Stack Size
;==============================================================================
 .SECTION  SSTACK, STACK, ALIGN=4
#if STACK_RESERVE == ON
        .EXPORT         __systemstack, __systemstack_top
 __systemstack:
        .RES.B          STACK_SYS_SIZE
 __systemstack_top: 
#endif
 
        .SECTION  USTACK, STACK, ALIGN=4
#if STACK_RESERVE == ON
         .EXPORT        __userstack, __userstack_top
 __userstack:
        .RES.B          STACK_USR_SIZE
 __userstack_top:
 
#endif
;==============================================================================
; 5.2 Define Sections
;==============================================================================
        .section        DATA,  data,  align=4
        .section        INIT,  data,  align=4
        .section        CONST, const, align=4
        .section        INTVECT, const, align=4 
#if CPLUSPLUS == ON
        .section        EXT_CTOR_DTOR, const, align=4  ; C++ constructors
#endif        
        
;==============================================================================
;6.             S T A R T 
;==============================================================================
;-----------------------------------------------------------
; MACRO WAIT_LOOP
;-----------------------------------------------------------
#macro wait_loop loop_number
#local _wait64_loop
        ldi             #loop_number, r0
_wait64_loop:
        add             #-1, r0
        bne             _wait64_loop
#endm
        .section        CODE, code, align=4
        .section        CODE_START, code, align=4



__start:                                        ; start point   

        ANDCCR          #0xEF                   ; disable interrupts   
        STILM           #LOW_PRIOR              ; set interrupt level to low prior

;==============================================================================
; NOT RESET YET 
;==============================================================================

startnop: 
        nop     
          
; If the debugger stays at this NOP after download of application, the controller has
; not been reset yet. In order to reset all hardware registers it is
; highly recommended to reset the controller.
; However, if no reset is used on purpose, this start address can also be used.
; This mechanism is using the .END instruction at the end of this mo-
; dule. It is not necessary for controller operation but improves reliability 
; of debugging (mainly emulator debugger). If the debugger stays here after a
; single step from label "_start" to label "startnop", the note can be ignored.      
;==============================================================================
;6.1             Clock startup
;==============================================================================
#if (CLOCKSOURCE != NOCLOCK)
;==============================================================================
; 6.1.1         Set PLL Multiplier
;==============================================================================
        LDI             #0x0484, R0             ; Clock source control reg CLKR
        LDI             #(PLLSPEED << 4), R1    ; Use PLL x1, enable PLL         
        STB             R1, @R0                 ; store data to CLKR register 
;==============================================================================
; 6.1.2         Start PLLs 
;==============================================================================             
#if ( ( CLOCKSOURCE == MAINPLLCLOCK ) || ( PSCLOCKSOURCE == PSCLOCK_PLL ) )
        LDI             #0x0484, R0             ; Clock source control reg CLKR
        LDI             #0x04, R1               ; Use PLL x1, enable PLL 
        ORB             R1, @R0                 ; store data to CLKR register       
#endif
       
       
#if ENABLE_SUBCLOCK == ON
        LDI             #0x0484, R0             ; Clock source control reg CLKR
        LDI             #0x08, R1               ; enable subclock operation
        ORB             R1, @R0                 ; store data to CLKR register
#endif                 
;==============================================================================
; 6.1.3         Wait for PLL oscillation stabilisation
;==============================================================================
#if ((CLOCKSOURCE==MAINPLLCLOCK)||(PSCLOCKSOURCE==PSCLOCK_PLL))
        LDI             #0x0482, R0             ; TimeBaseTimer TBCR
        LDI             #0x10, R1               ; set 256us 
        STB             R1, @R0
        LDI             #0x90, R1               ; set interrupt flag for simulator
        STB             R1, @R0
        
        LDI             #0x0483, R0             ; clearTimeBaseTimer CTBR
        LDI             #0xA5, R1                 
        STB             R1, @R0
        LDI             #0x5A, R1                 
        STB             R1, @R0

        LDI:20          #0x0482, R0
PLLwait:        
        BTSTH           #8, @R0
        BEQ             PLLwait
#endif
;==============================================================================
; 6.1.4         Set clocks 
;==============================================================================
;==============================================================================
; 6.1.4.1       Set CPU and peripheral clock 
;==============================================================================
; CPU and peripheral clock are set in one register
        LDI             #0x0486, R2             ; Set DIVR0 (CPU-clock (CLKB)  
        LDI             #((CPUCLOCK << 4) + PERCLOCK), R3           ; Load CPU clock setting
        STB             R3, @R2               
;==============================================================================
; 6.1.4.2       Set External Bus interface clock
;==============================================================================
; set External Bus clock
; Be aware to do smooth clock setting, to avoid wrong clock setting
; Take care, always write 0 to the lower 4 bits of DIVR1 register
        LDI             #0x0487, R2             ; Set DIVR1  
        LDI             #(EXTBUSCLOCK << 4), R3 ; Load Peripheral clock setting
        STB             R3, @R2 
;==============================================================================
; 6.1.4.3       Set CAN clock prescaler
;==============================================================================
; Set CAN Prescaler, only clock relevant parameter 
        LDI             #0x01A8, R0             ; Set CAN ClockParameter Register
        LDI             #CANCLOCK, R1           ; Load Divider
        STB             R1, @R0                 ; Set Divider
;==============================================================================
; 6.1.4.4       Switch Main Clock Mode
;==============================================================================
#if CLOCKSOURCE == MAINCLOCK
;==============================================================================
; 6.1.4.5       Switch Subclock Mode
;==============================================================================
#elif ( (CLOCKSOURCE == SUBCLOCK) )
    #if ENABLE_SUBCLOCK == ON
        LDI             #0x0484, R0             ; Clock source control reg CLKR
        LDI             #0x01, R1               ; load value to select main clock
        ORB             R1, @R0                 ; enable subclock as clock source       
    #else
        #error: Wrong setting! The clock source is subclock, but the subclock is disabled.
#endif      
;==============================================================================
; 6.1.4.6       Switch to PLL Mode
;==============================================================================
#elif ( (CLOCKSOURCE == MAINPLLCLOCK) )
        LDI             #0x0484, R0             ; Clock source control reg CLKR
        BORL            #0x2, @R0               ; enable PLL as clock source  
#endif

#endif  /* #endif CLOCKMODE != NOCLOCK */
;==============================================================================
;6.2  Set BusInterface
;==============================================================================
#if (EXTBUS)
;==============================================================================
;6.2.1  Set CS0
;==============================================================================
#if (CS0)
        LDI             #0x0640, R1             ; area select reg asr0
        LDI             #AREASEL0, R0           ; Start address of CS0 area 
        STH             R0, @R1                 ; set register
        LDI             #0x642, R1              ; area control reg ACR0
        LDI             #CONFIGCS0, R2          ; load settings
        STH             R2, @R1                 ; set register
        LDI             #0x660, R1              ; area wait register awr0
        LDI             #WAITREG0, R2           ; wait settings
        STH             R2, @R1                 ; set register
#endif
;==============================================================================
;6.2.2  Set CS1  
;==============================================================================
#if CS1
        LDI             #0x0644, R1             ; area select reg asr1
        LDI             #AREASEL1, R0           ; Start address of CS1 area 
        STH             R0, @R1                 ; set register
        LDI             #0x646, R1              ; area control reg ACR1
        LDI             #CONFIGCS1, R2          ; load settings
        STH             R2, @R1                 ; set register
        LDI             #0x662, R1              ; area wait register awr1
        LDI             #WAITREG1, R2           ; wait settings
        STH             R2, @R1                 ; set register
#endif
;==============================================================================
;6.2.3  Set CS2  
;==============================================================================
#if CS2
        LDI             #0x0648, R1             ; area select reg asr2
        LDI             #AREASEL2, R0           ; Start address of CS2 area 
        STH             R0, @R1                 ; set register
        LDI             #0x64A, R1              ; area control reg ACR2
        LDI             #CONFIGCS2, R2          ; load settings
        STH             R2, @R1                 ; set register
        LDI             #0x664, R1              ; area wait register awr2
        LDI             #WAITREG2, R2           ; wait settings
        STH             R2, @R1                 ; set register
#endif
;==============================================================================
;6.2.4  Set CS3  
;==============================================================================
#if CS3
        LDI             #0x064C, R1             ; area select reg asr3
        LDI             #AREASEL3, R0           ; Start address of CS3 area 
        STH             R0, @R1                 ; set register
        LDI             #0x64E, R1              ; area mode reg ACR3
        LDI             #CONFIGCS3, R2          ; load settings
        STH             R2, @R1                 ; set register
        LDI             #0x666, R1              ; area wait register awr3
        LDI             #WAITREG3, R2           ; wait settings
        STH             R2, @R1                 ; set register
#endif
;
;==============================================================================
;6.2.5   set Port Function Register
;==============================================================================    
;==============================================================================
;6.2.5.1   set EPFR2 Register. External bus mode (Addr[16-23]) or General purpose port
;==============================================================================    
        LDI             #0x0602, R1             ; Port Function Register 0, (PFR00)
        LDI             #EPFUNC2, R0            ; load port settings 
        STB             R0, @R1                 ; set register    
;==============================================================================
;6.2.5.2   set EPFRE Register. External bus mode (Addr[0-7]) or General purpose port
;==============================================================================      
        LDI             #0x060E, R1             ; Port Function Register 1, (PFR01)
        LDI             #EPFUNCE, R0            ; load port settings 
        STB             R0, @R1                 ; set register 
;==============================================================================
;6.2.5.3   set EPFRF Register. External bus mode (Addr[8-15]) or General purpose port
;==============================================================================      
        LDI             #0x060F, R1             ; Port Function Register 2, (PFR02)
        LDI             #EPFUNCF, R0            ; load port settings 
        STB             R0, @R1                 ; set register
;==============================================================================
;6.2.5.4   set EPFR3 Register. External bus mode (Control Signals) or General purpose port
;==============================================================================      
        LDI             #0x0603, R1             ; Port Function Register 8, (PFR08)
        LDI             #EPFUNC3, R0            ; load port settings 
        STB             R0, @R1                 ; set register 
;==============================================================================
;6.2.5.5   set EPFR9 Register. External bus mode (Control Signals) or General purpose port
;==============================================================================      
        LDI             #0x0609, R1             ; Port Function Register 9, (PFR09)
        LDI             #EPFUNC9, R0            ; load port settings 
        STB             R0, @R1                 ; set register 
;
;==============================================================================
;6.2.6  Enable used CS
;==============================================================================
        LDI             #0x0680, R1             ; chip select enable register CSER
        LDI             #CSENABLE, R0           ; load enable settings
        STB             R0, @R1                 ; set register
#endif  /* #endif busmode */
;==============================================================================
; 6.2.7   Set Flash wait cycles
;==============================================================================

#if  FLASH_READ_ONLY == ON              
        
        LDI     #0x7004,R0              ; Set FLWC (flash memory wait register)
        LDI     #0x01,R1                ; Set 1 wait cylce
        STB     R1,@R0
          
 #else 
        LDI     #0x7004,R0              ; Set FLWC (flash memory wait register)
        LDI     #0x03,R1                ; Set 3 wait cylces
        STB     R1,@R0 
 #endif 


;==============================================================================
; Standard C startup
;==============================================================================
;==============================================================================
;6.3  initialise Stack Pointer and Table Base register
;==============================================================================       
#if STACKUSE == SYSSTACK       
        ldi             #__systemstack_top, sp   ; initialize SP
#endif
#if STACKUSE == USRSTACK
        ldi             #__userstack_top, sp     ; initialize SP
#endif

        ldi             #INTVECT, R0             ; set Table Base
        mov             r0, tbr
;==============================================================================
;6.4  Clear data 
;==============================================================================
;       clear DATA section
; According to ANSI, the DATA section must be cleared during start-up

        ldi:8           #0, r0
        ldi             #sizeof DATA &~0x3, r1
        ldi             #DATA, r13
        cmp             #0, r1
        beq             data_clr1
data_clr0:
        add2            #-4, r1
        bne:d           data_clr0
        st              r0, @(r13, r1)
data_clr1:
        ldi:8           #sizeof DATA & 0x3, r1
        ldi             #DATA + (sizeof DATA & ~0x3), r13

        cmp             #0, r1
        beq             data_clr_end
data_clr2:
        add2            #-1, r1
        bne:d           data_clr2
        stb             r0, @(r13, r1)
data_clr_end:
;==============================================================================
;6.5  Copy Init section from ROM to RAM
;==============================================================================
; copy rom
; All initialised data's (e.g. int i=1) must be stored in ROM/FLASH area. 
; (start value)
; The Application must copy the Section (Init) into the RAM area.
        ldi             #_RAM_INIT, r0
        ldi             #_ROM_INIT, r1
        ldi             #sizeof(INIT), r2
        cmp             #0, r2
        beq:d           copy_rom_end
        ldi             #3, r12
        and             r2, r12
        beq:d           copy_rom2
        mov             r2, r13
        mov             r2, r3
        sub             r12, r3
copy_rom1:
        add             #-1, r13
        ldub            @(r13, r1), r12
        cmp             r3, r13
        bhi:d           copy_rom1
        stb             r12, @(r13, r0)
        cmp             #0, r3
        beq:d           copy_rom_end
copy_rom2:
        add             #-4, r13
        ld              @(r13, r1), r12
        bgt:d           copy_rom2
        st              r12, @(r13, r0)
copy_rom_end:

;==============================================================================
;6.6 C library initialization
;==============================================================================
#if CLIBINIT == ON
       call32          __stream_init, r12         ; initialise library 
#endif
;==============================================================================
;6.7  call C++ constructors
;==============================================================================
#if CPLUSPLUS == ON
       ldi              #___call_dtors, r4
       call32           _atexit, r12

       ldi              #EXT_CTOR_DTOR, r8
       ldi              #EXT_CTOR_DTOR + sizeof(EXT_CTOR_DTOR), r9
       cmp              r9, r8
       beq              L1
L0:
       ld               @r8, r10
       call:d           @r10
       add              #4, r8
       cmp              r9, r8
       bc               L0
L1:
#endif

start_main:
;==============================================================================
;6.8 call main routine
;==============================================================================
       ldi:8            #0, r4                    ; Set the 1st parameter for main to 0.
       call32:d         _main, r12
       nop
#if CLIBINIT == ON
       ldi:8            #0, r5                    ; Set the 2nd parameter for main to NULL.
       call32           _exit, r12
       __exit:
#endif

#if CPLUSPLUS == ON
       __abort:
#endif


;==============================================================================
;6.9   Return from main function
;==============================================================================
end: 
        bra             end  
        .end            __start