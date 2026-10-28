/* rgp:protos */
#define RGP_SELF_ActInfoClsnLinInitShort_230d80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Same slot as ActInfoClsnLinInitFull_230d30 with the last two values pinned.  The `mtc1
   $0,$f1` / `mtc1 $3,$f0` pair says those two constants live in FLOAT
   registers, i.e. named float locals -- a bare 0.0f store would be `sw $0`. */

typedef struct {
    f32 m00;
    f32 m04;
    s32 m08;
    s32 m0C;
    f32 m10;
    f32 m14;
} Slot;

void ActInfoClsnLinInitShort_230d80(Slot *o, s32 a, s32 b, f32 x, f32 y)
{
    f32 z = 0.0f;
    f32 w = 1.0f;

    o->m00 = 0.0f;
    o->m04 = 0.0f;
    o->m08 = 0;
    o->m0C = 0;
    o->m10 = 0.0f;
    o->m14 = 1.0f;
    if (a != 0 && b != 0) {
        o->m00 = x;
        o->m04 = y;
        o->m08 = a;
        o->m0C = b;
        o->m10 = z;
        o->m14 = w;
    }
}
