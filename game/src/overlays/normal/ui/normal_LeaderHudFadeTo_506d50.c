/* rgp:protos */
#define RGP_SELF_normal_LeaderHudFadeTo_506d50 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00506D50 -- `(a - p->fB0) / b` stored, then `a` stored, with the
 * second store in the `jr`'s delay slot.  The `nop` after `div.s` is mwcc's
 * own hazard padding.
 * One of the 55 unnamed functions. */
typedef struct Obj {
    u8  pad000[0xB0];
    f32 fB0;
    f32 fB4;
    f32 fB8;
} Obj;

void normal_LeaderHudFadeTo_506d50(Obj *p, f32 a, f32 b)
{
    p->fB8 = (a - p->fB0) / b;
    p->fB4 = a;
}
