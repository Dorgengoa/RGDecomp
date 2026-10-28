/* rgp:protos */
#define RGP_SELF_InsectDataStackRelease_31a790 1
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

extern s32 D_0047F230;
extern u8 D_004E7FB0[];

void InsectDataStackRelease_31a790(void)
{
    s32 r0;
    s32 t0;

    r0 = GetCurrentScene_1f5be0();
    MemStackClear_14dff0(D_004E7FB0);
    t0 = D_0047F230;
    if (t0 >= 0) {
        RecStackPop_1c4140(r0, t0);
    }
    D_0047F230 = -1;
}
