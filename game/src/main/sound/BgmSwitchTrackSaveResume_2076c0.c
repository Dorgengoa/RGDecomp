/* rgp:protos */
#define RGP_SELF_BgmSwitchTrackSaveResume_2076c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern void Sprintf_1343b8(void *, void *, s32);
/*rgp*/
/*rgp*/
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

void BgmSwitchTrackSaveResume_2076c0(s32 p0, s32 p1)
{
    u128 v40[8];
    s32 r0;
    s16 t0;
    s32 r1;
    s32 r3;
    s16 t1;
    s16 t2;
    s32 r8;

    if (p0 >= 0) {
        r0 = ((s32)GetStreamMgr_207ea0());
        t0 = D_00481C84;
        if (t0 == p0) {
            D_00481C80 = t0;
            D_00481C88 = t0;
            r1 = (BgmSetResumeWaitChan_207e80(-1), (s32)0);
            StreamMgrSetChanVolume_1d6430(r0, 0, 1.0f);
            return;
        }
        r3 = (StreamMgrPauseChan_1d6630(r0, 0), (s32)0);
        t1 = D_00481C80;
        if (t1 < 0) {
            t2 = D_00481C84;
            if (t2 > 0) {
                D_00481C80 = t2;
                StreamMgrChanSaveResumePoint_1d64c0(r0, 0);
            }
        }
        StreamMgrStopChan_1d66b0(r0, 0);
        if (p0 > 0) {
            Sprintf_1343b8(v40, D_0045C5C0, p0);
            StreamMgrStartChan_1d66f0(r0, 0, v40, (p1 & 0xFF));
            r8 = (StreamMgrPlayChan_1d6670(r0, 0, 0.0f), (s32)0);
            StreamMgrSetChanVolumeFade_1d63a0(r0, 0, 0, 1.0f);
            D_00481C84 = p0;
        } else {
            D_00481C84 = p0;
        }
        D_00481C88 = p0;
        return;
    }
}
