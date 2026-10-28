/* rgp:protos */
#define RGP_SELF_ActInfoClsnLinInitFull_230d30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* MEASURED, 8-arm sweep (build/zz/sw-q04-ActInfoClsnLinInitFull_230d30): the two-branch
   `bnel $6,$0,BLOCK+4 / b END / nop` guard comes ONLY from an `||` EARLY
   RETURN.  `a != 0 && b != 0`, nested ifs, two sequential `if (x == 0)
   return;`, `!a`, and `!(a == 0 || b == 0)` all give ONE identical object,
   two words short. */

typedef struct {
    f32 m00;
    f32 m04;
    s32 m08;
    s32 m0C;
    f32 m10;
    f32 m14;
} Slot;

void ActInfoClsnLinInitFull_230d30(Slot *o, s32 a, s32 b, f32 x, f32 y, f32 z, f32 w)
{
    o->m00 = 0.0f;
    o->m04 = 0.0f;
    o->m08 = 0;
    o->m0C = 0;
    o->m10 = 0.0f;
    o->m14 = 1.0f;
    if (a == 0 || b == 0) {
        return;
    }
    o->m00 = x;
    o->m04 = y;
    o->m08 = a;
    o->m0C = b;
    o->m10 = z;
    o->m14 = w;
}
