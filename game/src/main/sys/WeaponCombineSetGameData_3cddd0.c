/* rgp:protos */
#define RGP_SELF_WeaponCombineSetGameData_3cddd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern struct Obj0 * D_004838B8;
extern s32 D_004838BC;

struct Obj0;

struct Obj0 {
    u8 pad000[0x8];
    s32 m08;
};

s32 WeaponCombineSetGameData_3cddd0(struct Obj0 *p0)
{
    s32 rv0;
    s32 t0;

    rv0 = 1;
    if (p0 == 0) {
        rv0 = 0;
    } else {
        D_004838B8 = p0;
        t0 = p0->m08;
        D_004838BC = t0;
        rv0 = 1;
    }
    return rv0;
}
