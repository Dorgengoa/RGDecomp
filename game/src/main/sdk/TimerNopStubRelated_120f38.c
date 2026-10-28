#include "types.h"

/* Two-instruction stub, `jr $31; nop` only -- no body at all. Fully naked
   asm void, same trivial-stub shape as EntryPad_100000/GetLibcEhSemaId_120728 (s37/s38
   REG). Registers: only $31 -- no risk per REGINFOSCREEN. */

asm void TimerNopStubRelated_120f38(void)
{
    .set noreorder;
    jr $31;
    nop;
}
