/* rgp:protos */
#define RGP_SELF_TimeOfDayLightCopy_18d140 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct V4_18D { f32 x, y, z, w; } V4_18D;
typedef struct B64_18D { s32 b[0x10]; } B64_18D;
typedef struct B192_18D { u8 b[0xC0]; } __attribute__((aligned(16))) B192_18D;
typedef struct B32_18D { s32 b[0x8]; } B32_18D;

typedef struct T18D140 {
    f32 m00;
    u8 pad04[0xC];
    V4_18D m10;
    V4_18D m20;
    B64_18D m30;
    B64_18D m70;
    s32 mB0;
    u8 padB4[0xC];
    B192_18D mC0;
    V4_18D m180;
    V4_18D m190;
    s32 m1A0;
    B32_18D m1A4;
} T18D140;

T18D140 *TimeOfDayLightCopy_18d140(T18D140 *d, T18D140 *s)
{
    d->m00 = s->m00;
    d->m10 = s->m10;
    d->m20 = s->m20;
    d->m30 = s->m30;
    d->m70 = s->m70;
    d->mB0 = s->mB0;
    d->mC0 = s->mC0;
    d->m180 = s->m180;
    d->m190 = s->m190;
    d->m1A0 = s->m1A0;
    d->m1A4 = s->m1A4;
    return d;
}
