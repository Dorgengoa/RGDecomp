/* rgp:protos */
#define RGP_SELF_InfoEdgeCfgDataNum_39a290 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00482334;
extern s32 D_004835A8;
extern s32 D_004835AC;

s32 InfoEdgeCfgDataNum_39a290(s32 p0)
{
    s32 r0;
    s32 t0;
    s32 r1;

    r0 = VariantGetInt_15f780(p0);
    D_004835A8 = r0;
    t0 = D_00482334;
    r1 = ((s32)MemStackNew_14e1b0((((r0 * 0x24) + r0) << 1), t0));
    D_004835AC = r1;
    return 1;
}
