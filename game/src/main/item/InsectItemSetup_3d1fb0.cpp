/* rgp:protos */
#line 1
#include "types.h"

typedef struct Stat {
    u8 pad0[0x12];
    s16 h12;        /* 0x12 */
    s16 h14;        /* 0x14 */
    s16 h16;        /* 0x16 */
    u8 b18;         /* 0x18 */
    u8 b19;         /* 0x19 */
    u8 b1A;         /* 0x1A */
    u8 pad1B;
    s16 h1C;        /* 0x1C */
    s16 h1E;        /* 0x1E */
    u8 pad20[6];
    u8 b26;         /* 0x26 */
    u8 b27;         /* 0x27 */
    u8 f0 : 1;      /* 0x28 */
    u8 f1 : 1;
    u8 pad29[7];
    s32 m30;        /* 0x30 */
} Stat;

typedef struct Def {
    u8 pad0[8];
    s16 h8;         /* 0x08 */
    s16 hA;         /* 0x0A */
    s8 cC;          /* 0x0C */
    s8 cD;          /* 0x0D */
    s8 cE;          /* 0x0E */
    s8 cF;          /* 0x0F */
    s8 c10[12];     /* 0x10 */
    s16 h1C;        /* 0x1C */
    s16 h1E;        /* 0x1E */
} Def;

class Obj {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    s32 v7(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, int, int, int), 0x24, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
    
    
    void v10() { VCM0(void, 0x30); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v74(s32 a0) { VCM(void, (void *, s32), 0x130, a0); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v97(s32 a0, s32 a1) { VCM(void, (void *, s32, s32), 0x18C, a0, a1); }

    u8 pad4[0xC];
    s32 m10;        /* 0x10 */
    u8 pad14[4];
    Stat *st;       /* 0x18 */
};

typedef struct Snd {
    u8 pad0[0x10];
    s32 m10;
} Snd;

extern "C" {
s32 Rand_133710(void);
f32 RandFloat_13c010(void);
void StateFlagSet_3ccb70(s32, s32, s32, s32);
void ItemSetup_3d4ff0(Obj *, s32, s32, s32);
Def *ItemDefGetInsectData_40e0b0(s32);
extern s32 D_00465B00[];
extern s32 D_00465B08[];
extern s32 D_00465D80[];
extern f32 D_0047D2D4;
extern Snd *D_004838E8;
}

static inline bool inRange(s32 x)
{
    return x >= D_00465B00[0] && x <= D_00465B08[0];
}

extern "C" s32 InsectItemSetup_3d1fb0(Obj *o, s32 a1, s32 lvl, s32 kind)
{
    Def *d;
    s32 lo;
    s32 n;
    s32 t;
    s32 i;
    s32 v;
    bool ok;

    ok = lvl >= D_00465B00[0];
    o->st = 0;
    if (ok) {
        ok = lvl <= D_00465B08[0];
    }
    if (!ok && !(u8)o->v7((int)(long)(a1), (int)(long)(lvl), (int)(long)(kind))) {
        return 0;
    }
    ItemSetup_3d4ff0(o, a1, lvl, kind);
    if (o->m10 == 0) {
        o->v10();
        return 0;
    }
    d = ItemDefGetInsectData_40e0b0(o->m10);
    if (d == 0) {
        o->v10();
        return 0;
    }
    lo = d->h1C;
    n = d->h1E - lo + 1;
    t = lo + (s16)(s32)((f32)n * RandFloat_13c010());
    if (t <= 0) {
        t = 1;
    }
    if (t > 0xFF) {
        t = 0xFF;
    }
    o->st->b19 = t;
    o->st->b1A = o->st->b19;
    lo = d->h8;
    n = d->hA - lo + 1;
    o->st->h14 = lo + (s16)(s32)((f32)n * RandFloat_13c010());
    o->st->h16 = o->st->h14;
    o->st->b18 = (s32)(D_0047D2D4 * (f32)(s32)(f32)D_00465D80[0] * RandFloat_13c010());
    o->st->m30 = 0;
    lo = d->cC;
    n = d->cD - lo + 1;
    o->st->h1C = lo + (s16)(s32)((f32)n * RandFloat_13c010());
    lo = d->cE;
    n = d->cF - lo + 1;
    o->st->h1E = lo + (s16)(s32)((f32)n * RandFloat_13c010());
    for (i = 0; i < 6; i++) {
        lo = d->c10[i * 2];
        n = d->c10[i * 2 + 1] - lo + 1;
        o->v97(i, lo + (s16)(s32)((f32)n * RandFloat_13c010()));
    }
    o->st->b26 = Rand_133710() % 5;
    o->st->b27 = 1;
    o->st->h12 = 0;
    o->st->f0 = (s32)(2.0f * RandFloat_13c010()) != 0;
    o->st->f1 = 0;
    if (Rand_133710() % 30 < 3) {
        v = Rand_133710() % 3 + 7;
    } else {
        v = Rand_133710() % 7;
    }
    o->v74(v);
    switch (kind) {
    case 0x424A:
        StateFlagSet_3ccb70(D_004838E8->m10, 0x187, 1, 0);
        break;
    case 0x41ED:
    case 0x41EE:
    case 0x41F1:
        StateFlagSet_3ccb70(D_004838E8->m10, 0x186, 1, 0);
        break;
    }
    return 1;
}
