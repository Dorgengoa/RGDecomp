/* rgp:protos */
#line 1
#include "types.h"


typedef struct Iter {
    s32 a;
    s32 b;
} Iter;

typedef struct Elem {
    u8 pad0[0x1C];
    unsigned char b0 : 1;
    unsigned char b1 : 1;
    unsigned char b2 : 1;
    unsigned char b3 : 1;
} __attribute__((aligned(8))) Elem;

typedef struct Inner {
    u8 pad0[0xC];
    u8 *xC;
} Inner;

typedef struct Mid {
    u8 pad0[0x94];
    Inner *x94;
} Mid;

typedef struct Self {
    u8 pad0[8];
    Mid *x8;
    u8 padC[4];
    s32 x10;
} Self;

extern "C" {
extern Elem *IterNext_370040(Iter *);
extern void IterReset_3700f0(Iter *);
extern void IterInit_370170(Iter *, u8 *, int, int);
extern void StateVarSet_3cc9c0(s32, s32, s16, s32);
extern void StateFlagSet_3ccb70(s32, s32, bool, s32);
extern void HunterBountyRefreshProgress_3fdb80(Elem *);
extern f32 D_0047D88C;
s32 HunterBountyUpdateAll_3e9050(Self *arg0, int rgp_a1, int rgp_a2, int rgp_a3);
}

s32 HunterBountyUpdateAll_3e9050(Self *arg0, int rgp_a1, int rgp_a2, int rgp_a3) {
    Mid *m;
    Iter it __attribute__((aligned(16)));
    Elem *e;
    u8 *p;
    s32 c3;
    s32 c2;
    s32 c1;
    s32 c0;
    s32 v;
    bool flag;

    m = arg0->x8;
    if (m == 0) {
        return 0;
    }
    p = m->x94->xC;
    if (p != 0) {
        p += 0x88;
    }
    IterInit_370170(&it, p, (int)rgp_a2, (int)rgp_a3);
    while (e = IterNext_370040(&it), e != 0) {
        HunterBountyRefreshProgress_3fdb80(e);
    }
    c3 = 0;
    c2 = 0;
    c1 = 0;
    c0 = 0;
    IterReset_3700f0(&it);
    while ((e = IterNext_370040(&it)) != 0) {
        if (e->b0) {
            c1++;
            if (e->b3) {
                c0++;
            }
        } else {
            c3++;
            if (e->b3) {
                c2++;
            }
        }
    }
    v = (s32)((f32)c2 / (f32)c3 * 100.0f + D_0047D88C);
    flag = 0;
    if (v < 0) {
        v = 0;
    } else if (v >= 100) {
        flag = 1;
        v = 100;
    }
    StateFlagSet_3ccb70(arg0->x10, 0x1E4, flag, 0);
    StateVarSet_3cc9c0(arg0->x10, 0x68, v, 0);
    v = (s32)((f32)c0 / (f32)c1 * 100.0f + D_0047D88C);
    flag = 0;
    if (v < 0) {
        v = 0;
    } else if (v >= 100) {
        flag = 1;
        v = 100;
    }
    StateFlagSet_3ccb70(arg0->x10, 0x1E2, flag, 0);
    StateVarSet_3cc9c0(arg0->x10, 0x66, v, 0);
    return 1;
}
