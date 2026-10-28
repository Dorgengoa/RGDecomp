#include "types.h"

/* Two pad nops immediately before `entry` (0x00100008) -- retail has no
   jr $31 anywhere, execution falls straight through into `entry`. Same
   shape as the already-merged CrtRootExitThread_100220 (s37 REG): fully naked asm void
   with nothing auto-appended. */

asm void EntryPad_100000(void)
{
    .set noreorder;
    nop;
    nop;
}
