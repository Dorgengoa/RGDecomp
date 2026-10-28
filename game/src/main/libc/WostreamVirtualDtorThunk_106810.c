#include "types.h"

/* Multiple-inheritance "this"-adjustor thunk, sibling of OstreamVirtualDtorThunk_1067f0
   (same shape, different fixed adjustment/target). See that file for the
   naked-asm-vs-asm-volatile mechanism note. */

extern void WostreamDtor_103510(void);

asm void WostreamVirtualDtorThunk_106810(void)
{
    .set noreorder;
    lw    $25, 0x48($4);
    addiu $4, $4, -0x8;
    j     WostreamDtor_103510;
    addu  $4, $4, $25;
}
