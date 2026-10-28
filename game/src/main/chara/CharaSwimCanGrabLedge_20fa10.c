/* rgp:protos */
#define RGP_SELF_CharaSwimCanGrabLedge_20fa10 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_propagation off
#pragma opt_common_subs off

typedef struct Vec { f32 x, y, z, w; } Vec;
typedef struct Obj { u8 pad[0x70]; Vec pos; u8 pad2[0x440 - 0x80]; Vec dir; u8 pad3[0x3D8 - 0x450 + 0x100]; } ObjX;

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
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0045B080[4];
extern f32 D_0047D5D0;
extern f32 D_0047D94C;

s32 CharaSwimCanGrabLedge_20fa10(u8 *arg0) {
    Vec a __attribute__((aligned(16)));
    Vec b __attribute__((aligned(16)));
    Vec c __attribute__((aligned(16)));
    Vec e __attribute__((aligned(16)));
    Vec f __attribute__((aligned(16)));
    s32 tgt;
    f32 rad;
    f32 r;
    f32 h;
    f32 y;
    f32 lim;

    if (!(*(s64 *)(arg0 + 0x570) & 2)) return 0;
    if (!(*(s32 *)(arg0 + 0x3D8) & 0x10)) return 0;
    tgt = ((s32)CharaGetHangLedge_238260((void *)arg0));
    if (CharaHangLedgeIsValid_23a280(tgt) == 0) return 0;
    CharaGetForwardVec_238830(arg0, &a);
    CharaHangLedgeGetNormal_23a1f0(tgt, &b, 0);
    if (VecDot3_1cba90(&a, &b) < D_0047D5D0) return 0;
    CharaHangLedgeGetPos_23a230(tgt, &c);
    CharaHangLedgeClosestPoint_23a1a0(tgt, &e, &c);
    r = 0.5f * (rad = D_0045B080[0]);
    if (!(VecDistSq_1cb3c0(&c, &e) <= r * r)) {
        y = c.y;
        CharaGetPos_2388a0(arg0, &c);
        c.y = y;
        CharaHangLedgeClosestPoint_23a1a0(tgt, &e, &c);
        { f32 t = D_0045B080[0]; h = 0.5f * t; }
        r = (h + CharaGetCollRadius_2386a0(arg0)) * (h + CharaGetCollRadius_2386a0(arg0));
        if (!(VecDistSq_1cb3c0(&c, &e) <= r)) return 0;
    }
    VecCopy_1cbe30(&f, arg0 + 0x440);
    VecSub_1cbd00(&a, &e, arg0 + 0x70);
    r = D_0047D5D0 * VecLengthXZ_1cb490(&f);
    r = r * VecLengthXZ_1cb490(&a);
    if (VecDotXZ_1cba70(&f, &a) <= r) return 0;
    if (*(s32 *)(arg0 + 0x3D8) & 4) {
        lim = (0.0f + CharaGetCollHeight_2385f0(arg0)) + D_0047D94C * rad;
        if (e.y - CharaGetGroundY_238350(arg0) <= lim) return 0;
    }
    return 1;
}
