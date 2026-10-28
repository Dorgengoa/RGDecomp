/* rgp:protos */
#define RGP_SELF_IdBitmapGetCount_1f50c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef struct P1F50C0 { s16 m00; s16 m02; s32 m04; s32 m08; } P1F50C0;
s32 IdBitmapGetCount_1f50c0(P1F50C0 *p)
{
    s32 a;
    s32 b;
    s32 d;
    s32 r;

    /* mwcc issues these two halfword loads in the REVERSE of source order. */
    a = *(volatile s16 *)&p->m00;
    b = p->m02;
    d = b - a;
    if (p->m08 < d) {
        r = p->m08;
    } else {
        r = d;
    }
    return r;
}
