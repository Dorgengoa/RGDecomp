/* rgp:protos */
#define RGP_SELF_McBuildSaveDirPath_376460 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern void strcpy(s32, void *);
extern void Sprintf_1343b8(s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_00463A00[];

void McBuildSaveDirPath_376460(s32 p0, s32 p1)
{
    strcpy(p0, D_00463A00);
    Sprintf_1343b8(p0, p0, p1);
}
