#include "types.h"

/* Multiple-inheritance "this"-adjustor thunk: loads a fixed offset out of
   the vtable footer at $4+0x48, adjusts the incoming `this` by -8, adds the
   loaded offset in the delay slot, then TAIL-CALLS the real target with a
   raw `j` (not `jal`) -- this function never itself executes `jr $31`;
   OstreamDtor_102fd0's own return goes straight back to whoever called this
   thunk. `asm volatile{}` auto-appends its own epilogue and reschedules the
   `j`'s delay slot (measured: moves `j` before `addiu`, inserts an extra
   `jr $31`); fully naked `asm void` sidesteps both, verbatim transcription
   only -- see naked-asm-void-reginfo-gap: $4/$25 are both in the normal
   C-visible register set, so no .reginfo risk here. */

extern void OstreamDtor_102fd0(void);

asm void OstreamVirtualDtorThunk_1067f0(void)
{
    .set noreorder;
    lw    $25, 0x48($4);
    addiu $4, $4, -0x8;
    j     OstreamDtor_102fd0;
    addu  $4, $4, $25;
}
