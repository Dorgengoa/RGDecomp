/* rgp:protos */
#define RGP_SELF_FontSetGlyphTable_26f730 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
extern s32 memcpy(s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 FontSetGlyphTable_26f730(s32 p0, s32 p1, s32 p2)
{
    s32 v3C;
    s32 rv3;
    s32 r0;
    s32 t0;
    s32 rv2;
    s32 r1;

    if (p1 == 0) {
        rv3 = 0;
    } else {
        v3C = 0;
        r0 = ((s32)FontGetGlyphTable_26f6a0(p0, &v3C));
        t0 = v3C;
        rv2 = 1;
        if ((t0 < p2) != 0) {
            rv2 = 0;
        } else {
            r1 = ((s32)memcpy(r0, p1, p2));
            rv2 = 1;
        }
        rv3 = rv2;
    }
    return rv3;
}
