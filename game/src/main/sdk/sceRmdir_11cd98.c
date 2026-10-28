/* rgp:protos */
#define RGP_SELF_sceRmdir_11cd98 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma tailcall off

/* mwcc at -O4 turns this into a tail `j`; retail keeps the frame and the
   `jal`, with both delay slots filled.  `#pragma tailcall off` is the only
   thing in the 244-name pragma namespace that reproduces it -- the four
   optimization_level settings give either the tail call (3, 4) or an
   unscheduled 9-word frame (1, 2). */

extern s32 FileIoPathCmdRpc_11ca10(void *, s32);

void sceRmdir_11cd98(void *p0)
{
    FileIoPathCmdRpc_11ca10(p0, 0x8);
}
