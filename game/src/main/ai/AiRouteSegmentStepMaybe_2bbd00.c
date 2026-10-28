/* rgp:protos */
#define RGP_SELF_AiRouteSegmentStepMaybe_2bbd00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Vec {
    f32 x, y, z, w;
} Vec;

typedef struct Seg {
    Vec p;
    u8 pad10[0x10];
} Seg;

typedef struct Self {
    u8 pad000[0x1C0];
    Seg seg[4];
    u32 w240[4];
    s8 n250;
    s8 cur251;
    u8 pad252[0x10];
    s8 cnt262;
} Self;

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
extern f32 D_0047D278;
extern f32 D_0047DB78;
extern f32 D_0047DB7C;
extern f32 D_0047EDC0;
extern f32 D_0047EDC4;
extern f32 D_0047EDC8;
extern f32 D_0047EDCC;

s32 AiRouteSegmentStepMaybe_2bbd00(Self *self, s32 *arg1, s32 arg2, s32 idx) {
    Vec pos __attribute__((aligned(16)));
    Vec out __attribute__((aligned(16)));
    f32 thr[4] __attribute__((aligned(16)));
    Vec tmpA __attribute__((aligned(16)));
    Vec tmp9 __attribute__((aligned(16)));
    s32 h;
    u32 *ps;
    Seg *sg;
    f32 d0;
    f32 d1;
    u32 w;
    s8 c;
    f32 lim;

    if (arg1 == 0 || (h = *arg1) == 0) {
        return 0;
    }
    if (!(idx < self->n250 - 1)) {
        return 1;
    }
    ps = (u32 *)((u8 *)self + 0x240) + idx;
    if (((*ps & 0xFF00) >> 8) != 3 && self->seg[idx + 1].p.y <= 10.0f + self->seg[idx].p.y) {
        goto ret0;
    }
    CharaGetPos_2388a0(h, &pos);
    sg = &self->seg[idx];
    d0 = VecDistSqXZ_1cb390(sg, &pos);
    sg = &self->seg[idx + 1];
    d1 = SegmentProjectT_1ca340(&pos, &self->seg[idx], sg);
    w = *ps;
    thr[0] = D_0047EDC0;
    thr[1] = D_0047EDC4;
    thr[2] = D_0047EDC8;
    thr[3] = D_0047EDCC;
    lim = thr[w & 0xFF];
    if ((!(d1 <= D_0047DB78) && d1 <= D_0047DB7C) || d0 <= lim) {
        if (AiDirWithinCone_2bcd10(self, &tmpA, arg2, &pos, sg, D_0047D278) != 0) {
            if (self->cnt262 >= 0 && (((*ps & 0xFF00) >> 8) == 3 || AiPointClearOfCharasMaybe_2bc920(self, h, sg) != 0)) {
                CharaAddFlags_212460(h, (long long)(0x10002));
            } else {
                c = self->cnt262;
                if (c < 0) {
                    self->cnt262 = c + 1;
                }
            }
            return 1;
        }
        AiPointFromChara_2bcca0(self, &out, h, &tmpA);
        AiMoveDispatch_2be5f0(self, arg1, &out, &tmpA, AiGetKeepDistanceMaybe_2c0f90(self));
        return 1;
    }
    if (((w & 0xFF00) >> 8) == 3 && !(d0 <= VecDistSqXZ_1cb390(sg, &pos))) {
        idx++;
        self->cur251 = idx;
    }
    AiPointFromDir_2bcc10(self, &out, &tmp9, &pos, &self->seg[idx]);
    AiMoveDispatch_2be5f0(self, arg1, &out, &tmp9, AiGetApproachMarginMaybe_2c0fc0(self));
    return 1;
ret0:
    return 0;
}
