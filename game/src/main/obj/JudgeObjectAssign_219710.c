/* rgp:protos */
#define RGP_SELF_JudgeObjectAssign_219710 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct V4_219 { f32 x, y, z, w; } V4_219;
typedef struct W27_219 { s32 b[27]; } W27_219;
typedef struct H40_219 { s16 b[40]; } H40_219;
typedef struct C40_219 { s8 b[40]; } C40_219;

typedef struct T219710 {
    V4_219 m00;
    W27_219 m10;
    s32 m7C;
    s32 m80;
    s16 m84;
    s16 m86;
    s16 m88;
    s16 m8A;
    s16 m8C;
    s16 m8E;
    s32 m90;
    f32 m94;
    f32 m98;
    f32 m9C;
    s32 mA0;
    s16 mA4;
    s16 mA6;
    u8 padA8[0xC];
    s16 mB4;
    s16 mB6;
    s16 mB8;
    s16 mBA;
    s16 mBC;
    u16 mBE;
    s16 mC0;
    u8 padC2[2];
    f32 mC4;
    f32 mC8;
    f32 mCC;
    H40_219 mD0;
    C40_219 m120;
    u8 pad148[8];
    V4_219 m150;
    V4_219 m160;
    V4_219 m170;
} T219710;

T219710 *JudgeObjectAssign_219710(T219710 *d, T219710 *s)
{
    d->m00 = s->m00;
    d->m10 = s->m10;
    d->m7C = s->m7C;
    d->m80 = s->m80;
    d->m84 = s->m84;
    d->m86 = s->m86;
    d->m88 = s->m88;
    d->m8A = s->m8A;
    d->m8C = s->m8C;
    d->m8E = s->m8E;
    d->m90 = s->m90;
    d->m94 = s->m94;
    d->m98 = s->m98;
    d->m9C = s->m9C;
    d->mA0 = s->mA0;
    d->mA4 = s->mA4;
    d->mA6 = s->mA6;
    d->mB4 = s->mB4;
    d->mB6 = s->mB6;
    d->mB8 = s->mB8;
    d->mBA = s->mBA;
    d->mBC = s->mBC;
    d->mBE = s->mBE;
    d->mC0 = s->mC0;
    d->mC4 = s->mC4;
    d->mC8 = s->mC8;
    d->mCC = s->mCC;
    d->mD0 = s->mD0;
    d->m120 = s->m120;
    d->m150 = s->m150;
    d->m160 = s->m160;
    d->m170 = s->m170;
    return d;
}
