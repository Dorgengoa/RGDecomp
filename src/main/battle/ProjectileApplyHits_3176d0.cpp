#include "types.h"
#pragma opt_strength_reduction off

typedef unsigned __int128 u128;

typedef struct {
    s16 m0;
    s16 m2;
    s16 m4;
    s16 m6;
    s16 m8;
    s16 mA;
    u8 padC[4];
    f32 x;
    f32 y;
    f32 z;
} Ent3176d0;

class Obj3176d0 {
public:
    u8 pad0[0x80];
    s32 m80;
    u8 pad84[0x8E - 0x84];
    s16 m8E;
    u8 pad90[0xB0 - 0x90];
    virtual s32 d0();
    virtual s32 d1();
    virtual s32 d2();
    virtual s32 d3();
    virtual s32 d4();
    virtual s32 d5();
    virtual s32 d6();
    virtual s32 d7();
    virtual s32 d8();
    virtual s32 d9();
    virtual s32 d10(s16);
    virtual s32 d11();
    virtual s32 d12();
    virtual s32 d13();
    virtual s32 d14();
    virtual s32 d15();
    virtual s32 d16();
    virtual s32 d17(void *);
    u8 padB4[4];
    s16 mB8;
    u8 padBA[0x170 - 0xBA];
    u128 m170;
    u8 pad180[0x1CC - 0x180];
    s32 m1CC;
    Ent3176d0 ent[1];
};

typedef struct {
    s32 x;
    s32 y;
    s32 z;
    s32 w;
    s16 h[7];
} Desc3176d0;

typedef struct {
    Obj3176d0 *obj;
    Desc3176d0 *d;
} Req3176d0;

extern "C" {
s32 BattleApplyHit_2ef930(Req3176d0 *);
void JudgeObjectApplyHitsNop_3141e0(Obj3176d0 *);
}

extern "C" void ProjectileApplyHits_3176d0(Obj3176d0 *arg0)
{
    Desc3176d0 d;
    Req3176d0 r;
    s32 i;
    s16 *pk;
    Ent3176d0 *e;
    s16 k;

    if (arg0->m1CC > 0 && arg0->d17(arg0) != 0) {
        for (i = 0; i < arg0->m1CC; i++) {
            pk = &((Ent3176d0 *)((u8 *)arg0 + i * 0x1C + 0x1D0))->m2;
            if (arg0->d10(*pk) != 0) {
                e = (Ent3176d0 *)((u8 *)arg0 + (u32)i * 0x1C + 0x1D0);
                k = e->m8;
                arg0->m8E = k;
                d.x = 0;
                d.y = 0;
                d.z = 0;
                d.w = 0x3F800000;
                d.h[0] = -1;
                d.h[1] = -1;
                d.h[2] = -1;
                d.h[3] = -1;
                d.h[4] = -1;
                d.h[5] = -1;
                d.h[6] = -1;
                d.h[0] = e->m0;
                d.h[1] = *pk;
                d.h[2] = e->m4;
                d.h[3] = e->m6;
                d.h[4] = e->mA;
                d.h[5] = arg0->mB8;
                d.h[6] = e->m8;
                *(f32 *)&d.x = e->x;
                *(f32 *)&d.y = e->y;
                *(f32 *)&d.z = e->z;
                d.w = 0x3F800000;
                r.d = &d;
                r.obj = arg0;
                if (BattleApplyHit_2ef930(&r) != 0) {
                    arg0->m170 = *(u128 *)&d;
                    arg0->m80 |= 2;
                    arg0->mB8++;
                }
            }
        }
        JudgeObjectApplyHitsNop_3141e0(arg0);
    }
}
