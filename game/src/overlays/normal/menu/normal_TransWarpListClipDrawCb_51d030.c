/* rgp:protos */
#define RGP_SELF_normal_TransWarpListClipDrawCb_51d030 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x0051D030 */

extern u8 D_004DB150[];

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_TransWarpListClipDrawCb_51d030(void *p, s32 b, s32 c, s32 d, s32 e)
{
    u8 *q;
    s32 t;
    s32 h;
    s32 w;

    q = D_004DB150;
    if (e != 0) {
        if (q != 0) {
            TextStyleSetClipRect_26f620(q, 0, 0x200, 0x127, 0x1AC);
        }
        if (p != 0) {
            GsPktOpenPrim_13f730(p, 6);
            GsPktWriteAD_13ec80(p, 0x40, ((u64)0x1AC0127 << 32) | 0x2000000);
            GsPktClose_13f5b0(p);
        }
    } else {
        if (q != 0) {
            TextStyleClearClipRect_26f600((void *)(q));
        }
        t = GetDrawCtx_15de80();
        h = DrawEnvGetWidth_1451e0(t);
        w = DrawEnvGetHeight_1451d0(t);
        if (p != 0) {
            GsPktOpenPrim_13f730(p, 6);
            GsPktWriteAD_13ec80(p, 0x40, ((u64)(h - 1) << 16) | ((u64)(w - 1) << 48));
            GsPktClose_13f5b0(p);
        }
    }
    return 1;
}
