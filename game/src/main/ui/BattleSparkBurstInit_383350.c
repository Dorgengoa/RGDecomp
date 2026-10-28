/* rgp:protos */
#define RGP_SELF_BattleSparkBurstInit_383350 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct E383350 {
    f32 f00;
    f32 f04;
    f32 f08;
    f32 f0C;
    s16 f10;
    s16 f12;
} E383350;

typedef struct T383350 {
    s16 f00;
    s16 f02;
    E383350 arr[32];
    s16 f284;
    s16 f286;
} T383350;

/*rgp*/

void BattleSparkBurstInit_383350(T383350 *self, s32 a, s32 b)
{
    E383350 *e;
    s32 i;
    s32 j;
    E383350 *f;

    self->f00 = (s16)a;
    self->f02 = (s16)b;
    self->f286 = 0x18;
    self->f284 = 0x18;
    e = self->arr;
    for (i = 0; i < self->f284; i++) {
        e->f00 = 0.0f;
        e->f04 = 0.0f;
        e->f08 = RandRangeFloat_1ca5d0(8.0f) - 4.0f;
        e->f0C = RandRangeFloat_1ca5d0(8.0f) - 4.0f;
        e->f00 = e->f00 + 2.0f * e->f08;
        e->f04 = e->f04 + 2.0f * e->f0C;
        e->f10 = (s16)RandRangeFloat_1ca5d0(10.0f) + 1;
        e++;
    }
    f = self->arr;
    for (j = 24; j < 32; j++) {
        f->f10 = 0;
        f++;
    }
}
