/* rg-override: replaces game/src/main/file/OverlayCdSeek_1c32b0.c sha256 d6735461ee3e539110c9391419d0e963fa26c78dfcc45d72a88d66a38109543c
 * why: native files (docs/NATIVE-FS.md, PLAN.md D9): the seek ahead of an overlay load
 *      (sceCdSeek to the .BIN's LSN) only hid disc latency; there is no drive. */
/* rgp:protos */
#define RGP_SELF_OverlayCdSeek_1c32b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma tailcall off
void OverlayCdSeek_1c32b0(s32 i)
{
    (void)i; /* rg-override: was sceCdSeek_12a908(D_004A6F80[i]) for i in 0..6 */
}
