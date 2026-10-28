/* rgp:protos */
#define RGP_SELF_CharaSetStickDirXYZMaybe_213ab0 1
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
    u8 pad000[0x430];
    f32 m430;
    f32 m434;
    f32 m438;
    s32 m43C;
};

void CharaSetStickDirXYZMaybe_213ab0(struct Obj0 *p0, f32 fa0, f32 fa1, f32 fa2)
{
    p0->m430 = fa0;
    p0->m434 = fa1;
    p0->m438 = fa2;
    p0->m43C = 0;
    VecNormalize_1cbb80((struct Obj0 *)((u8 *)p0 + 0x430), (struct Obj0 *)((u8 *)p0 + 0x430));
}
