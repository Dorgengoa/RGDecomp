/* rgp:protos */
#define RGP_SELF_ResGroupCmdObjSetIdMaybe_42aba0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern struct Obj0 * D_00483FFC;

struct Obj0;

struct Obj0 {
    s16 m00;
};

s32 ResGroupCmdObjSetIdMaybe_42aba0(s32 p0)
{
    struct Obj0 *r0;
    s32 r1;

    D_00483FFC = 0;
    r0 = ResGroupListCurElem_42a510();
    if (r0 == 0) {
        return 1;
    }
    r1 = VariantGetInt_15f780(p0);
    r0->m00 = r1;
    D_00483FFC = r0;
    return 1;
}
