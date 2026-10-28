/* rgp:protos */
#define RGP_SELF_ResGroupCmdLinkById_42b510 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00483FE0;

struct Obj0;

struct Obj0 {
    u8 pad000[0x20];
    s32 m20;
};

s32 ResGroupCmdLinkById_42b510(s32 p0)
{
    struct Obj0 *r0;
    s32 r1;
    s32 t0;
    s32 r2;

    r0 = ResGroupListCurElem_42a5d0();
    if (r0 == 0) {
        return 1;
    }
    r1 = VariantGetInt_15f780(p0);
    t0 = D_00483FE0;
    r2 = ResGroupListFindValueById_42c3a0(t0, r1);
    r0->m20 = r2;
    return 1;
}
