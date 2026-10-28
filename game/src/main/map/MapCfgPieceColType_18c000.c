/* rgp:protos */
#define RGP_SELF_MapCfgPieceColType_18c000 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00481258;

struct Obj0;

struct Obj0 {
    u8 pad000[0x8C];
    s32 m8C;
};

s32 MapCfgPieceColType_18c000(s32 p0)
{
    s32 t0;
    s32 rv2;
    struct Obj0 *r0;
    s32 r1;

    t0 = D_00481258;
    rv2 = 1;
    if (t0 == 0) {
        rv2 = 0;
    } else {
        r0 = ListNodeGetData_18bff0(t0);
        r1 = VariantGetInt_15f780(p0);
        r0->m8C = r1;
        rv2 = 1;
    }
    return rv2;
}
