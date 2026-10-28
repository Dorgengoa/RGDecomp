/* rgp:protos */
#define RGP_SELF_InvHasItemById_2c43f0 1
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
    u8 pad000[0x18];
    s32 m18;
};

u8 InvHasItemById_2c43f0(s32 p0)
{
    struct Obj0 *r0;
    s32 t0;
    s32 r1;

    r0 = GetGameData_1fede0();
    t0 = r0->m18;
    r1 = ((s32)InvFindInCategoryRange_3c8370(t0, p0, 0, -1, 0, 0));
    return (r1 != 0);
}
