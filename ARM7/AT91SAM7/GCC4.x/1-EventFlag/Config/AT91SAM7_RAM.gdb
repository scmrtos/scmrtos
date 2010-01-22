target remote localhost:2331
monitor reset 1
monitor long 0xFFFFFD44 = 0x00008000    # disable wdt
monitor sleep 10
monitor long 0xFFFFFD00 = 0xA5000004    # reset the peripherals
monitor sleep 50
monitor long 0xFFFFFC20 = 0x00000001    # OSC enable, no timeout
monitor sleep 50
monitor long 0xFFFFFC2C = 0x00190605    # Assuming 18.432 MHz OSC, PLLCK=MAINCK * 26 / 5, set LOCK after 6 SCLK
monitor sleep 50
monitor long 0xFFFFFC30 = 0x00000004    # PRES = 2 
monitor sleep 50
monitor long 0xFFFFFC30 = 0x00000007    # MCK = PLLCK / 2
monitor sleep 100
monitor long 0xFFFFFF00 = 0x00000001    # REMAP
monitor speed auto
break main
load
continue