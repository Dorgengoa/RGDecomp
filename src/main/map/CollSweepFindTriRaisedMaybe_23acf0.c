#include "types.h"

typedef struct R {
    u8  pad000[0x4];
    f32 m04;
    u8  pad008[0x8];
} R;

typedef struct W {
    u8  pad000[0x24];
    f32 m24;
    u8  pad028[0x58];
} W;

extern const f32 D_0045B080;
extern f32 D_0047DB14;

extern void VecCopy_1cbe30(R *r, void *d);
extern s32  CollSweepInit_1c81b0(W *w, R *r, s32 x, f32 t, f32 one);
extern s32  CollSweepTri_1c7790(W *w, void *a, void *b, void *c);

s32 CollSweepFindTriRaisedMaybe_23acf0(u8 *e, s32 n, s32 mask, void *d, s32 x, f32 *out)
{
    R   r;
    W   w;
    s32 best;
    s32 i;
    f32 t;
    f32 c;
    f32 g;

    if (e == 0 || n <= 0) return -1;
    VecCopy_1cbe30(&r, d);
    c = D_0045B080;
    g = D_0047DB14;
    t = 5.0f * (g * c);
    r.m04 = r.m04 + t;
    CollSweepInit_1c81b0(&w, &r, x, t, 1.0f);
    best = -1;
    for (i = 0; i < n; i++, e += 0x60) {
        if ((*(s16 *)(e + 0x46) & mask) != 0) continue;
        if (CollSweepTri_1c7790(&w, e, e + 0x10, e + 0x20) != 0) best = i;
    }
    if (best < 0) return -1;
    if (out != 0) *out = w.m24;
    return best;
}
