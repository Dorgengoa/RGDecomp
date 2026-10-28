/* rgp:protos */
#define RGP_SELF_DrawEventFrameTask_27a870 1
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

extern u8 D_004D7810[];

s32 DrawEventFrameTask_27a870(void)
{
    s32 r0;
    s32 r1;
    s32 r2;

    r0 = GetPauseStep_2f6660();
    if (r0 == 0) {
        r1 = (LetterboxFadeStep_2782a0(D_004D7810), (s32)0);
    }
    r2 = (LetterboxDraw_277ff0(D_004D7810), (s32)0);
    return r2;
}
