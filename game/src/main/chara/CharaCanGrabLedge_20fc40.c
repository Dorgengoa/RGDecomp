/* rgp:protos */
#define RGP_SELF_CharaCanGrabLedge_20fc40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Vec { f32 x, y, z, w; } Vec;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0045B080[4];
extern f32 D_0047D5D0;
extern f32 D_0047D94C;

#pragma opt_propagation off
s32 CharaCanGrabLedge_20fc40(u8 *arg0) {
    Vec a __attribute__((aligned(16)));
    Vec b __attribute__((aligned(16)));
    Vec c __attribute__((aligned(16)));
    Vec e __attribute__((aligned(16)));
    s32 tgt;
    f32 rad;
    f32 h;
    f32 r;
    f32 lim;

    tgt = ((s32)CharaGetHangLedge_238260((void *)arg0));
    if (CharaHangLedgeIsValid_23a280(tgt) == 0) return 0;
    CharaGetForwardVec_238830(arg0, &a);
    CharaHangLedgeGetNormal_23a1f0(tgt, &b, 0);
    if (VecDot3_1cba90(&a, &b) < D_0047D5D0) return 0;
    CharaHangLedgeGetPos_23a230(tgt, &c);
    CharaHangLedgeClosestPoint_23a1a0(tgt, &e, &c);
    if (c.y <= e.y) return 0;
    rad = D_0045B080[0];
    h = D_0047D5D0 * rad;
    r = (CharaGetCollRadius_2386a0(arg0) - (-h)) * (CharaGetCollRadius_2386a0(arg0) - (-h));
    if (!(VecDistSq_1cb3c0(&c, &e) <= r)) return 0;
    if (*(s32 *)(arg0 + 0x3D8) & 4) {
        lim = (0.0f + CharaGetCollHeight_2385f0(arg0)) + D_0047D94C * rad;
        if (e.y - CharaGetGroundY_238350(arg0) <= lim) return 0;
    }
    return 1;
}
