#include "types.h"
#pragma opt_propagation off

typedef struct {
    u8 pad0[0x8];
    s32 unk8;
    u8 padC[0x10 - 0xC];
    s16 *unk10;
} Obj0Arg0;

typedef struct {
    s32 unk0;
    s32 unk4;
    f32 unk8;
} Obj0Arg1;

extern f32 D_0047D24C;
extern f32 D_0047D424;

void EffCurveFindKeySpan_197700(Obj0Arg0 *arg0, Obj0Arg1 *arg1, f32 x)
{
    s32 n;
    s16 *tbl;
    s32 hi;
    f32 f;
    s32 lo;
    s32 mid;
    s16 a;
    s32 xi;
    s32 c;

    n = arg0->unk8;
    c = n > 0;
    if (!c) {
        arg1->unk4 = 0;
        arg1->unk0 = 0;
        arg1->unk8 = 0.0f;
        return;
    }
    xi = (s32)x;
    tbl = arg0->unk10;
    hi = n - 1;
    f = 0.0f;
    lo = 0;
    while (lo < hi) {
        mid = (lo + hi) / 2;
        if (!(tbl[mid] > xi)) {
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }
    arg1->unk0 = lo - 1;
    arg1->unk4 = lo;
    if (lo == 0) {
        arg1->unk0 = 0;
    } else if (arg1->unk0 >= arg0->unk8) {
        hi = arg0->unk8 - 1;
        arg1->unk4 = hi;
        arg1->unk0 = hi;
    } else {
        a = tbl[arg1->unk0];
        f = (f32)(tbl[lo] - a);
        if (!(f <= 0.0f)) {
            f = (x - (f32)a) / f;
        }
        if (f < D_0047D24C) {
            f = 0.0f;
        }
        if (!(f <= D_0047D424)) {
            arg1->unk0 = lo;
            f = 0.0f;
        }
    }
    arg1->unk8 = f;
}
