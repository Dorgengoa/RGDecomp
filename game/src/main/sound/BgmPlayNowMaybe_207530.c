/* rgp:protos */
#define RGP_SELF_BgmPlayNowMaybe_207530 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
extern void Sprintf_1343b8(void *, void *, s32);
/*rgp*/
typedef rg_u128 u128;

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_0045C5C0[];
extern s16 D_00481C80;
extern s16 D_00481C84;
extern s16 D_00481C88;

void BgmPlayNowMaybe_207530(s32 p0, s32 p1)
{
    u128 v40[8];
    s16 t0;
    s32 r0;

    if (p0 >= 0) {
        t0 = D_00481C84;
        if (t0 == p0) {
            return;
        }
        r0 = ((s32)GetStreamMgr_207ea0());
        StreamMgrPauseChan_1d6630(r0, 0);
        StreamMgrStopChan_1d66b0(r0, 0);
        if (p0 > 0) {
            Sprintf_1343b8(v40, D_0045C5C0, p0);
            StreamMgrStartChan_1d66f0(r0, 0, v40, (p1 & 0xFF));
        }
        D_00481C84 = p0;
        D_00481C88 = p0;
        D_00481C80 = -1;
        return;
    }
}
