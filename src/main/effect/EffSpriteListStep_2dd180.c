#include "types.h"

typedef struct E2dd180 {
    u8  pad00[0x28];
    f32 f28;
    f32 f2C;
    u8  pad30[0x10];
    f32 f40;
    f32 f44;
    f32 f48;
    f32 f4C;
    f32 f50;
    f32 f54;
    f32 f58;
    u8  pad5C[4];
    u8  m60[0x10];
    u8  m70[0x10];
    u8  m80[0x10];
    u8  m90[0x10];
    u8  mA0[0x10];
    u8  mB0[0x10];
} E2dd180;

typedef struct T2dd180 {
    u8  pad000[0x244];
    E2dd180 *f244;
    s16 f248;
} T2dd180;

extern void VecAdd_13be20(void *, void *, void *);

void EffSpriteListStep_2dd180(T2dd180 *self)
{
    E2dd180 *e;
    s32 i;

    e = self->f244;
    if (e != 0) {
        for (i = 0; i < self->f248; i++) {
            VecAdd_13be20(e->mA0, e->mA0, e->m60);
            VecAdd_13be20(e->m60, e->m60, e->m70);
            e->f40 = e->f40 + e->f44;
            e->f44 = e->f44 + e->f48;
            VecAdd_13be20(e->mB0, e->mB0, e->m80);
            VecAdd_13be20(e->m80, e->m80, e->m90);
            e->f28 = e->f28 + e->f4C;
            e->f2C = e->f2C + e->f50;
            e->f4C = e->f4C + e->f54;
            e->f50 = e->f50 + e->f58;
            e++;
        }
    }
}
