/* rgp:protos */
#define RGP_SELF_EvCmdWrapAngle_25d970 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x4];
    struct Obj1 *m04;
};

struct Obj1 {
    u8 pad000[0x4];
    f32 m04;
};

s32 EvCmdWrapAngle_25d970(struct Obj0 *p0)
{
    struct Obj1 * t0;
    f32 t1;
    f32 r0;
    s32 r1;

    t0 = p0->m04;
    t1 = p0->m04->m04;
    r0 = WrapAngle_13c050(t1);
    r1 = (ScriptSetRefFloat_26a1c0(p0, r0), (s32)0);
    return 1;
}
