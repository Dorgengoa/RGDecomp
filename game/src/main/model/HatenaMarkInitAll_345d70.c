/* rgp:protos */
#define RGP_SELF_HatenaMarkInitAll_345d70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00482DE0;

void HatenaMarkInitAll_345d70(void)
{
    s32 r0;
    s32 r1;
    s32 l2;
    s32 r3;
    s32 r4;

    r0 = ((s32)GetSystemMemStack_202600());
    r1 = GetCircleObj_1fdaf0();
    l2 = 0;
    do {
        r3 = ((s32)HatenaMarkListAdd_344f60(&D_00482DE0, r0, 0));
        r4 = HatenaMarkBindModel_3451a0(r3, r1);
        l2 = (l2 + 1);
    } while (l2 < 2);
}
