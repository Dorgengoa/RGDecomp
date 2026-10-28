/* rgp:protos */
#define RGP_SELF_GameDataLatchLeaderId_2f38e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00482780;

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x18];
    struct Obj1 *m18;
};

struct Obj1 {
    u8 pad000[0x18E];
    s16 m18E;
};

struct Obj0 *GameDataLatchLeaderId_2f38e0(void)
{
    struct Obj0 *r0;
    s16 t1;

    r0 = GetGameData_1fede0();
    t1 = r0->m18->m18E;
    D_00482780 = t1;
    return r0;
}
