#include "types.h"

typedef struct E3831d0 {
    f32 f00;
    f32 f04;
    f32 f08;
    f32 f0C;
    s16 f10;
    s16 f12;
} E3831d0;

typedef struct T3831d0 {
    s16 f00;
    s16 f02;
    E3831d0 arr[32];
    s16 f284;
    s16 f286;
} T3831d0;

extern f32 RandRangeFloat_1ca5d0(f32);

void BattleSparkBurstUpdate_3831d0(T3831d0 *self)
{
    E3831d0 *e;
    E3831d0 *base;
    s32 j;
    E3831d0 *f;

    if (self->f284 > 0) {
        base = self->arr;
        if (self->f286 < 0x20) {
            e = &base[self->f286];
            e->f00 = 0.0f;
            e->f04 = 0.0f;
            e->f08 = RandRangeFloat_1ca5d0(8.0f) - 4.0f;
            e->f0C = RandRangeFloat_1ca5d0(8.0f) - 4.0f;
            e->f00 = e->f00 + 2.0f * e->f08;
            e->f04 = e->f04 + 2.0f * e->f0C;
            e->f10 = (s16)RandRangeFloat_1ca5d0(10.0f) + 1;
            self->f286 = self->f286 + 1;
            self->f284 = self->f284 + 1;
        }
        f = self->arr;
        for (j = 0; j < 0x20; j++) {
            if (f->f10 > 0) {
                f->f00 = f->f00 + f->f08;
                f->f04 = f->f04 + f->f0C;
                f->f10 = f->f10 - 1;
                if (f->f10 <= 0) {
                    self->f284 = self->f284 - 1;
                }
            }
            f++;
        }
    }
}
