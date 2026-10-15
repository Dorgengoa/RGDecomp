#include "types.h"

typedef __int128 s128;

typedef struct {
    s128 a;
    s128 b;
} Blk;

typedef struct {
    f32 f0;
    u8 pad[0xC];
} Par;

typedef struct {
    u8 pad0[0x34];
    s16 unk34;
    u8 pad36[0x5C - 0x36];
    f32 unk5C;
    u8 pad60[0x10];
    u8 b0 : 1;
    u8 b1 : 1;
    u8 b2 : 1;
} A;

typedef struct {
    u8 pad0[0x4C];
    void *unk4C;
    void *unk50;
} M;

typedef struct {
    u8 pad0[4];
    M *unk4;
} R;

extern R *TreasureBoxResolveRec_33b180(A *);
extern void FrameSetRot_14a390(void *, void *);
extern void FrameSetPos_14a450(void *, void *);
extern s32 CollFrameTreeCollectTrisFwd_16c180(void *, u8 *, Blk *, s32);
extern void CollTriSetAttr_1ce5a0(u8 *, s32);
extern f32 D_0047D298;

static inline void clr(void *p, u32 n)
{
    u8 *q = (u8 *)p;
    if (q != NULL) {
        do {
            *q = 0;
            n--;
            q++;
        } while (n != 0);
    }
}

s32 TreasureBoxCollectCollPolys_3393f0(A *arg0, u8 *arg1, s32 arg2, Blk *arg3)
{
    Blk blk;
    Par par;
    R *r;
    M *m;
    void *a;
    void *b;
    f32 f;
    s32 n;
    s32 i;

    blk = *arg3;
    r = TreasureBoxResolveRec_33b180(arg0);
    if (r == NULL) {
        return 0;
    }
    if (!arg0->b2) {
        return 0;
    }
    m = r->unk4;
    if (m == NULL) {
        return 0;
    }
    a = m->unk50;
    b = m->unk4C;
    if (a != NULL) {
        f = 0.0f;
        if (arg0->unk5C != 0.0f) {
            f = D_0047D298;
        }
        { u8 *q=(u8*)&par;u32 n=16;if(q){do{*q=0;n--;q++;}while(n!=0);}}
        par.f0 = f;
        FrameSetRot_14a390(a, &par);
    }
    n = 0;
    if (b != NULL) {
        FrameSetPos_14a450(b, arg0);
        FrameSetRot_14a390(b, (u8 *)arg0 + 0x10);
        n = CollFrameTreeCollectTrisFwd_16c180(b, arg1, &blk, arg2);
        i = 0;
        while (i < n) {
            CollTriSetAttr_1ce5a0(arg1, arg0->unk34);
            i++;
            arg1 += 0x60;
        }
    }
    return n;
}
