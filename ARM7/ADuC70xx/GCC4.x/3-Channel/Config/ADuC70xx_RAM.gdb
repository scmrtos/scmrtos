target remote localhost:2331
monitor reset 1

monitor long 0xFFFF0010 = 0x00000000    # SWICFG: clear unmaskable ints
monitor long 0xFFFF000C = 0xFFFFFFFF    # IRQCLR: disable all maskable IRQ
monitor long 0xFFFF010C = 0xFFFFFFFF    # FIQCLR: disable all maskable FIQ
monitor long 0xFFFF0234 = 0x06          # RSTCLR: clear reset source bits, emulate power-on reset

monitor long 0xFFFF0308 = 0x0088        # T0CON: enable timer
monitor long 0xFFFF030C = 0x00          # T0CLRI: clear int flag
monitor long 0xFFFF0308 = 0x0000        # T0CON: disable timer
monitor long 0xFFFF0300 = 0x0000        # T0LD: clear

monitor long 0xFFFF0328 = 0x0088        # T1CON: enable timer
monitor long 0xFFFF032C = 0x00          # T0CLRI: clear int flag
monitor long 0xFFFF0328 = 0x0000        # T0CON: disable timer
monitor long 0xFFFF0320 = 0x0000        # T0LD: clear
# remap:
monitor long 0xFFFF0224 = 0x00          # Silicon bug? write-once 0 to remap area 0x000-0xFFF
monitor long 0xFFFF0220 = 0x01
echo " remapped " ;

monitor speed auto
break main
load
continue