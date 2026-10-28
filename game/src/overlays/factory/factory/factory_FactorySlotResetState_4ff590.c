/* rgp:protos */
#define RGP_SELF_factory_FactorySlotResetState_4ff590 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S {
    u8  pad00[0xE];
    s16 f0E;
    s16 f10;
    s16 f12;
    u8  pad14[0xC];
    s32 f20;
    s32 f24;
    s32 f28;
    f32 f2C;
    s16 f30;
    s16 f32;
    s16 f34;
} S;

void factory_FactorySlotResetState_4ff590(S *p)
{
    p->f0E = -1;
    p->f10 = -1;
    p->f12 = -1;
    p->f20 = 0;
    p->f24 = 0;
    p->f28 = 0;
    p->f2C = 1.0f;
    p->f30 = 0;
    p->f32 = 0;
    p->f34 = 0;
}
