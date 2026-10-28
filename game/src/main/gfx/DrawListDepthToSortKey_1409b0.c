/* rgp:protos */
#define RGP_SELF_DrawListDepthToSortKey_1409b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef struct Q140 { u8 pad000[0x20]; f32 f20; f32 f24; } Q140;
typedef struct S140 { u8 pad000[0xF20]; Q140 *fF20; u8 padF24[0x2CB0]; s32 f3BD4; } S140;
s32 DrawListDepthToSortKey_1409b0(S140 *p, f32 v)
{
    s32 n; Q140 *q; s32 r;
    q = p->fF20;
    n = p->f3BD4;
    r = (s32)((f32)n * (q->f24 - v) / (q->f24 - q->f20));
    if (r < 0) r = 0;
    if (n < r) r = n;
    return r;
}
