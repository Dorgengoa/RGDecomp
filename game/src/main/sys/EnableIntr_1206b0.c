#include "types.h"

/* Reads COP0 Status ($12), masks out bit 0x10000 (the EIE bit), re-enables
   interrupts (`ei`), returns 1 if bit was already clear i.e. interrupts
   were disabled before this call (0 != masked value -> was NOT already
   this bit). Omit jr $31: the trailing sltu is retail's delay-slot
   instruction. */

s32 EnableIntr_1206b0(void)
{
    asm volatile {
        mfc0  $2, $12
        lui   $3, 0x1
        and   $2, $2, $3
        ei
        sltu  $2, $0, $2
    }
}
