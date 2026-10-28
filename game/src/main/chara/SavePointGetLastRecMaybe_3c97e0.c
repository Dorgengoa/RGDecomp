/* rgp:protos */
#define RGP_SELF_SavePointGetLastRecMaybe_3c97e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern struct Obj1 * D_00483894;

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0xF8];
    s16 mF8;
};

struct Obj1 {
    u8 pad000[0x74];
    s32 m74;
};

s32 SavePointGetLastRecMaybe_3c97e0(struct Obj0 *p0)
{
    struct Obj1 * t0;
    s16 t1;
    s32 t2;
    s32 r0;

    t0 = D_00483894;
    if (t0 != 0) {
        t1 = p0->mF8;
        t2 = D_00483894->m74;
        r0 = GroupGetRecordById_425590(t2, t1);
        return r0;
    }
    return 0;
}
