#include "types.h"

typedef struct { f32 x, y, z, w; } Vec;
typedef struct { s16 a; s16 b; } Pair;
typedef struct { u8 f0 : 1; u8 f1 : 1; u8 rest : 6; } Bits;

typedef struct Obj {
    u8 pad0[0x4];
    s16 h4;
    s16 h6;
    s16 h8;
    s16 hA;
    s16 hC;
    u8 padE[0x2];
    s32 w10;
    s32 w14;
    s32 w18;
    s32 w1C;
    s32 w20;
    s32 w24;
    s32 w28;
    s16 h2C;
    Bits b2E;
    u8 pad2F[0x1];
    s16 h30;
    s16 h32;
    s16 h34;
    s16 h36;
    s16 h38;
    u8 pad3A[0x56];
    Vec v90;
    Vec vA0[3];
    s32 wD0[3];
    s32 wDC[3];
    s16 hE8;
    u8 padEA[0x6];
    s64 dF0;
    s16 hF8;
    u8 padFA[0x6];
    s64 d100;
    s16 h108;
    u8 pad10A[0x2];
    s32 w10C;
    s64 d110;
    s64 d118;
    s32 w120;
    s32 w124;
    f32 f128;
    f32 f12C;
    f32 f130;
    f32 f134;
    f32 f138;
    s16 h13C;
    u8 pad13E[0x2];
    s32 w140;
    u8 pad144[0xC];
    s32 w150;
    s32 w154;
    s32 w158;
    s32 w15C;
    s64 d160;
    void * p168;
    s32 w16C;
    u8 pad170[0x4];
    void * p174;
    s32 w178;
    Pair * p17C;
    s32 w180;
    s32 w184;
    s32 w188;
    s16 h18C;
    s16 h18E;
    s16 h190[3];
    s16 h196[7];
    Bits b1A4;
    u8 pad1A5[0x1];
    s16 h1A6;
    s16 h1A8;
    u8 pad1AA[0x2];
    s32 w1AC;
    s32 w1B0;
    s16 h1B4;
    u8 pad1B6[0x2];
    s64 d1B8;
    s16 h1C0[101];
    s16 h28A[32];
    u8 pad2CA[0x6];
    u8 sub2D0[16384];
    Bits b42D0;
    u8 pad42D1[0x3];
    s32 w42D4[16];
    s32 w4314[16];
    s32 w4354[16];
    s16 h4394[16][10];
    u8 pad44D4[0x504];
    s16 h49D8[16][10];
    s16 h4B18[16][10];
    s32 w4C58[2];
    s32 w4C60[2];
    s16 h4C68[16];
    s16 h4C88;
    u8 pad4C8A[0x2];
    s32 w4C8C;
    s32 w4C90;
    s32 w4C94;
    s32 w4C98;
    s16 h4C9C;
    Bits b4C9E;
    u8 pad4C9F[0x1];
    s16 h4CA0;
    u8 pad4CA2[0x2];
    s32 w4CA4;
    s16 h4CA8;
} Obj;

extern s32 VecCopy_1cbe30(Vec *, Vec *);
extern s32 PoolClear_36ade0(void *);
extern s32 PartyResetZoneListsMaybe_3cb210(Obj *, s32);
extern s32 Bitset131072Ctor_3cb880();
extern s32 GameRecReleaseAllSlots_3ce400(void *);
extern const f32 D_00465940[];
extern s32 D_00465B70[];

#define BZERO(d, n) { u8 *p_ = (u8 *)(d); u32 n_ = (n); if (p_) while (n_) { *p_ = 0; n_--; p_++; } }

void PartyReset_3cb300(Obj *p) {
    s32 i;
    s32 j;
    s32 k;
    Pair *q;

    p->h4 = -1;
    p->w14 = 0;
    p->h6 = -1;
    p->w18 = 0;
    p->h8 = -1;
    p->w1C = 0;
    p->hA = -1;
    p->w20 = 0;
    p->hC = -1;
    p->w24 = 0;
    p->w10 = -1;
    p->w28 = 0;
    p->h2C = -1;
    p->b2E.f0 = 0;
    p->h30 = -1;
    p->h4CA0 = -1;
    p->b42D0.f0 = 0;
    p->h32 = -1;
    p->h34 = 1;
    p->h36 = 1;
    p->h38 = 1;
    p->h4CA8 = -1;
    p->b1A4.f0 = 0;
    p->h1A6 = -1;
    p->h1A8 = -1;
    p->w1AC = 0;
    p->w1B0 = 0;
    {
    Vec zero = {0};
    VecCopy_1cbe30(&p->v90, &zero);
    for (i = 0; i < 3; i++) {
        VecCopy_1cbe30(&p->vA0[i], &zero);
        p->wD0[i] = 0;
        p->wDC[i] = 0;
    }
    }
    PartyResetZoneListsMaybe_3cb210(p, 0);
    p->hE8 = -1;
    p->dF0 = 0;
    p->hF8 = -1;
    p->d100 = 0;
    p->h1B4 = -1;
    p->d1B8 = 0;
    p->h108 = -1;
    p->w10C = 0;
    p->b42D0.f1 = 0;
    p->d110 = 0;
    p->d118 = 0;
    p->w120 = 0;
    p->w124 = 0;
    p->f128 = D_00465940[0];
    p->f12C = D_00465940[0];
    p->f130 = D_00465940[0];
    p->f134 = D_00465940[0];
    p->f138 = 11.0f;
    p->h13C = 0;
    p->w140 = 0;
    p->w150 = 0;
    p->w154 = 0;
    p->w158 = 0;
    p->w15C = 0;
    p->d160 = 0;
    if (p->p168 != 0) {
        PoolClear_36ade0(p->p168);
    }
    p->w16C = 0;
    if (p->p174 != 0) {
        GameRecReleaseAllSlots_3ce400(p->p174);
    }
    p->w178 = 0;
    if (p->p17C != 0) {
        for (i = 0; i < D_00465B70[0]; i++) {
            q = &p->p17C[i];
            q->a = -1;
            q->b = 0;
        }
    }
    p->w180 = 0;
    p->w184 = 0;
    p->w188 = -1;
    p->h4C88 = -1;
    p->w4C8C = 0;
    p->w4C90 = 100;
    p->w4C94 = 100;
    p->w4CA4 = 100;
    p->w4C98 = 100;
    p->h4C9C = -1;
    p->h18C = 3;
    p->h18E = -1;
    for (i = 0; i < 3; i++) {
        p->h190[i] = -1;
    }
    for (i = 0; i < 7; i++) {
        p->h196[i] = -1;
    }
    p->b4C9E.f0 = 0;
    for (i = 0; i < 101; i++) {
        p->h1C0[i] = 0;
    }
    for (i = 0; i < 32; i++) {
        p->h28A[i] = 0;
    }
    for (i = 0; i < 16; i++) {
        p->h4C68[i] = 0;
    }
    Bitset131072Ctor_3cb880(p->sub2D0);
    for (i = 0; i < 2; i++) {
        p->w4C58[i] = 0;
        p->w4C60[i] = 0;
    }
    for (j = 0; j < 16; j++) {
        p->w42D4[j] = 0;
        p->w4314[j] = 0;
        p->w4354[j] = 0;
        for (k = 0; k < 10; k++) {
            p->h4394[j][k] = 0;
            p->h49D8[j][k] = 0;
            p->h4B18[j][k] = 0;
        }
    }
}
