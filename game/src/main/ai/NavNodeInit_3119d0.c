/* rgp:protos */
#define RGP_SELF_NavNodeInit_3119d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    f32 m00;
    f32 m04;
    f32 m08;
    u8 pad00C[0x4];
    s32 m10;
    u8 pad014[0x4];
    s16 m18;
};

void NavNodeInit_3119d0(struct Obj0 *p0, s32 p1, s32 p2, f32 fa0, f32 fa1, f32 fa2)
{
    NavNodeClear_311a50(p0);
    p0->m18 = p1;
    p0->m10 = p2;
    p0->m00 = fa0;
    p0->m04 = fa1;
    p0->m08 = fa2;
}
