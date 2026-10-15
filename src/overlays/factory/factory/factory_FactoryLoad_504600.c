#include "types.h"

typedef struct Anim {
    s16 f00;
    s16 f02;
    u8  pad04[0x8];
} Anim;

typedef struct Scr {
    u8   pad00[0x20];
    Anim f20[4];
    s32  f50;
    u8   pad54[0x14];
    u8   f68[0x4];
} Scr;

extern u8 D_0050CE58[];
extern u8 D_0050CE68[];
extern u8 D_0050CE78[];
extern u8 D_0050CE88[];
extern u8 D_0050CE90[];
extern u8 D_0050CE98[];

extern s32  factory_FactoryCursorModelLoad_504250(Scr *o, s32 a, s32 b, s32 c, u8 *p, u8 *q);
extern void func_1CCB00(Anim *a);
extern void func_1CCB70(Anim *a);
extern void func_1CCBB0(Anim *a, u8 *p);

void factory_FactoryLoad_504600(Scr *o)
{
    s32 i;

    if (o->f50 == 1) {
        return;
    }
    if (o->f50 == 2) {
        return;
    }
    if (o->f50 == 3) {
        func_1CCBB0(&o->f20[0], D_0050CE58);
        func_1CCBB0(&o->f20[1], D_0050CE68);
        func_1CCBB0(&o->f20[2], D_0050CE78);
        o->f50 = 4;
        return;
    }
    for (i = 0; i < 4; i++) {
        func_1CCB00(&o->f20[i]);
    }
    switch (o->f50) {
    case 4:
        if (o->f20[0].f02 == 0) {
            return;
        }
        if (o->f20[0].f02 == 1 && factory_FactoryCursorModelLoad_504250(o, 0, 0, 0x2A4, D_0050CE88, o->f68) != 0) {
            o->f50 = 5;
        } else {
            o->f50 = 1;
        }
        break;
    case 5:
        if (o->f20[1].f02 == 0) {
            return;
        }
        if (o->f20[1].f02 == 1 && factory_FactoryCursorModelLoad_504250(o, 1, 1, 0x2A4, D_0050CE90, o->f68) != 0) {
            o->f50 = 6;
        } else {
            o->f50 = 1;
        }
        break;
    case 6:
        if (o->f20[2].f02 == 0) {
            return;
        }
        if (o->f20[2].f02 == 1 && factory_FactoryCursorModelLoad_504250(o, 2, 2, 0x2A4, D_0050CE98, o->f68) != 0) {
            o->f50 = 7;
        } else {
            o->f50 = 1;
        }
        break;
    case 7:
        o->f50 = 2;
        break;
    }
    switch (o->f50) {
    case 2:
    case 1:
        for (i = 0; i < 4; i++) {
            func_1CCB70(&o->f20[i]);
        }
        break;
    }
}
