/* rgp:protos */
#define RGP_SELF_MovCfgStrDup_311e50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
extern s32 strcpy(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 MovCfgStrDup_311e50(s32 p0)
{
    s32 r0;
    s32 r1;
    s32 r2;

    r0 = StrSizeWithNul_1cac60(p0);
    r1 = MovCfgScratchAllocAlign4_311f40(r0);
    if (r1 == 0) {
        return 0;
    }
    r2 = ((s32)strcpy(r1, p0));
    return r1;
}
