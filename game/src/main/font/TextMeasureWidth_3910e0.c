/* rgp:protos */
#define RGP_SELF_TextMeasureWidth_3910e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 TextMeasureWidth_3910e0(s32 p0)
{
    s32 v6C;
    s32 v68;
    s32 v20[18] __attribute__((aligned(16)));
    s32 r2;
    s32 t0;

    TextStyleInit_26c610(v20);
    TextStyleInitWithFontType_2931c0(v20, (long long)(2));
    r2 = (FontMeasureString_26daf0(v20, p0, &v6C, &v68), (s32)0);
    t0 = v6C;
    return t0;
}
