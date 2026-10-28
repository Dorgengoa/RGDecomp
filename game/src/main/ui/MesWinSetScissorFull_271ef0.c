/* rgp:protos */
#define RGP_SELF_MesWinSetScissorFull_271ef0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void MesWinSetScissorFull_271ef0(s32 p0, s32 p1, s32 p2)
{
    s32 r0;
    s32 r1;
    s32 r2;
    s32 r3;
    s32 r4;
    s32 r5;

    r0 = ((unsigned char)MesWinGetClipMode_2721d0(p0));
    if (r0 == 0) {
        return;
    }
    r1 = MesWinGetLineFixedPos_272440(p0, p2);
    if (r1 != 0) {
        return;
    }
    r2 = GetDrawCtx_15de80();
    r3 = DrawEnvGetWidth_1451e0(r2);
    r4 = DrawEnvGetHeight_1451d0(r2);
    r5 = (GsPktWriteAD_13ec80(p1, 0x40, (((s64)(r3 - 1)) << 16) | (((s64)(r4 - 1)) << 48)), (s32)0);
}
