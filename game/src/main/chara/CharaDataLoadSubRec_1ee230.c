/* rgp:protos */
#define RGP_SELF_CharaDataLoadSubRec_1ee230 1
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
    u8 pad000[0x8];
    s32 m08;
};

struct Obj1 {
    u8 pad000[0x60];
    s16 m60;
};

u8 CharaDataLoadSubRec_1ee230(struct Obj1 *p0, struct Obj0 *p1)
{
    s32 t0;
    s32 r0;
    s32 r1;
    s32 rv2;
    s16 t1;

    t0 = p1->m08;
    r0 = CharaDataRecFindSubRec_1ee1e0(p0, t0);
    if (r0 == 0) {
        return (u8)0;
    }
    r1 = CharaDataSubRecAddLoad_1ee830(r0, p1);
    rv2 = 4;
    if (r1 != 0) {
        p0->m60 = 2;
        rv2 = 2;
    } else {
        p0->m60 = 4;
        rv2 = 4;
    }
    t1 = p0->m60;
    return (t1 == 2);
}
