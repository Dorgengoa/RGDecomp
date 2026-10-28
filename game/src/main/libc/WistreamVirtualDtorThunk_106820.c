#include "types.h"

/* Multiple-inheritance "this"-adjustor thunk, sibling of OstreamVirtualDtorThunk_1067f0
   (same shape, different fixed adjustment/target). See that file for the
   naked-asm-vs-asm-volatile mechanism note. */

extern void WistreamDtor_1035b0(void);

asm void WistreamVirtualDtorThunk_106820(void)
{
    .set noreorder;
    lw    $25, 0x48($4);
    addiu $4, $4, -0x18;
    j     WistreamDtor_1035b0;
    addu  $4, $4, $25;
}
