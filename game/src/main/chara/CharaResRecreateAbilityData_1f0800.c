/* rgp:protos */
#define RGP_SELF_CharaResRecreateAbilityData_1f0800 1
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

struct Obj0 {
    u8 pad000[0x2];
    s16 m02;
};

s32 CharaResRecreateAbilityData_1f0800(s32 p0, s32 p1)
{
    struct Obj0 *r0;
    s16 t0;
    s32 r1;

    r0 = CharaResFindById_1efba0(p0, p1);
    if (r0 == 0) {
        return 0;
    }
    t0 = r0->m02;
    r1 = CharaAbilityDataRecreate_1f0840(p0, t0);
    return r1;
}
