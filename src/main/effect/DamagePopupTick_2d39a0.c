#include "types.h"

typedef struct Obj {
    u8 pad0[4];
    f32 f4;
    u8 pad8[0x14];
    f32 f1C;
    f32 f20;
    f32 f24;
    u8 pad28[4];
    s16 cnt;
    s16 max;
    u8 pad30[4];
    s32 t;
    s32 mode;
    u8 b0 : 1;
    u8 b1 : 7;
} Obj;

extern f32 D_0047DAA8;
extern const f32 D_0047DACC __attribute__((section(".sdata")));
extern f32 D_0047DAD0;

void DamagePopupTick_2d39a0(Obj *o)
{
    f32 f;

    if (!o->b0) {
        return;
    }
    o->cnt++;
    if (o->max > o->cnt) {
        return;
    }
    o->cnt = o->max;
    if (o->mode == 0) goto blk;
    if (o->mode == 3) goto blk;
    if (o->mode == 4) {
blk:
        if (o->t < 21) {
            o->f4 += o->f20;
            o->f20 += o->f24;
        }
        if (o->t >= 30) {
            o->f1C = f = o->f1C - D_0047DAA8;
            if (f < 0.0f) {
                o->f1C = 0.0f;
            }
        }
        if (++o->t > 45) {
            o->b0 = 0;
            o->t = 0;
        }
    }
    if (o->mode == 1) {
        o->f4 += o->f20;
        o->f20 += D_0047DACC;
        if (o->t >= 10) {
            o->f1C = f = o->f1C - D_0047DAA8;
            if (f < 0.0f) {
                o->f1C = 0.0f;
            }
        }
        if (++o->t > 45) {
            o->b0 = 0;
            o->t = 0;
        }
    }
    if (o->mode == 2) goto blk2;
    if (o->mode == 5) goto blk2;
    if (o->mode == 6) {
blk2:
        if (o->t < 16) {
            o->f4 += o->f20;
            o->f20 += D_0047DACC;
        }
        if (o->t >= 25) {
            o->f1C = f = o->f1C - D_0047DAD0;
            if (f < 0.0f) {
                o->f1C = 0.0f;
            }
        }
        if (++o->t > 45) {
            o->b0 = 0;
            o->t = 0;
        }
    }
}
