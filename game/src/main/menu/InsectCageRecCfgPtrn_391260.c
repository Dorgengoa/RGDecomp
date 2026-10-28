/* rgp:protos */
#define RGP_SELF_InsectCageRecCfgPtrn_391260 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern struct Obj0 * D_00483440;
extern struct Obj0 * D_00483444;

struct Obj0;

struct Obj0 {
    u8 pad000[0x2];
    s16 m02;
};

s32 InsectCageRecCfgPtrn_391260(s32 p0)
{
    s32 r0;
    struct Obj0 * t0;
    s16 t1;
    s16 t2;

    r0 = VariantGetInt_15f780(p0);
    t0 = D_00483440;
    t1 = D_00483440->m02;
    if (t1 >= 9) {
        return 1;
    }
    D_00483444 = (struct Obj0 *)((u8 *)(struct Obj0 *)((u8 *)t0 + (t1 << 4)) + 4);
    t2 = D_00483440->m02;
    D_00483440->m02 = (t2 + 1);
    return 1;
}
