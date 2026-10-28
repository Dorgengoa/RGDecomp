/* rgp:protos */
#define RGP_SELF_StreamChanReset_1d75d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S1D7 {
    s8  f00;
    u8  pad001[0x7F];
    s16 f80;
    u8  pad082[2];
    f32 f84;
    u8  pad088[4];
    f32 f8C;
    s32 f90;
    s32 f94;
    s32 f98;
    s32 f9C;
    s16 fA0;
    s16 fA2;
    s32 fA4;
    u8  padA8[4];
    s32 fAC;
} S1D7;

void StreamChanReset_1d75d0(S1D7 *p)
{
    p->f80 = -1;
    p->f84 = 0.0f;
    p->f8C = p->f84;
    p->f90 = 0;
    p->f00 = 0;
    p->f98 = 0;
    p->f9C = 0;
    p->fA0 = 0;
    p->fA2 = 0;
    p->fA4 = 0;
    p->f94 = 0;
    p->fAC = -1;
}
