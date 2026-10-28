/* rgp:protos */
#define RGP_SELF_BgmRequestTrack_2077e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
extern s16 D_00481C80;
extern s16 D_00481C84;
extern s16 D_00481C88;
extern s8 D_00481C8C;

void BgmRequestTrack_2077e0(s32 arg0, s32 arg1) {
    s32 t;

    if (arg0 < 0) return;
    t = ((s32)GetStreamMgr_207ea0());
    if (D_00481C84 == arg0) {
        if (D_00481C88 != arg0) {
            StreamMgrSetChanVolumeFade_1d63a0(t, 0, 0x3C, 1.0f);
            D_00481C88 = arg0;
        }
        return;
    }
    if (D_00481C88 != arg0) {
        StreamMgrSetChanVolumeFade_1d63a0(t, 0, 0x1E, 0.0f);
        D_00481C88 = arg0;
        D_00481C80 = -1;
        D_00481C8C = arg1;
    }
}
