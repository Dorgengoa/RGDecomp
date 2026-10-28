/* rgp:protos */
#define RGP_SELF_CharaSetMoveDirXYZMaybe_213a90 1
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
    u8 pad000[0x450];
    f32 m450;
    f32 m454;
    f32 m458;
    s32 m45C;
};

void CharaSetMoveDirXYZMaybe_213a90(struct Obj0 *p0, f32 fa0, f32 fa1, f32 fa2)
{
    p0->m450 = fa0;
    p0->m454 = fa1;
    p0->m458 = fa2;
    p0->m45C = 0;
    VecNormalize_1cbb80((struct Obj0 *)((u8 *)p0 + 0x450), (struct Obj0 *)((u8 *)p0 + 0x450));
}
