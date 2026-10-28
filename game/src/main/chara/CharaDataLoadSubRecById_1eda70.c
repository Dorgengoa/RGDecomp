/* rgp:protos */
#define RGP_SELF_CharaDataLoadSubRecById_1eda70 1
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
    s32 m00;
};

s32 CharaDataLoadSubRecById_1eda70(s32 p0, struct Obj0 *p1)
{
    s32 t0;
    s32 r0;
    s32 r1;

    t0 = p1->m00;
    r0 = CharaDataFindById_1ed990(p0, t0);
    if (r0 == 0) {
        return 0;
    }
    r1 = ((unsigned char)CharaDataLoadSubRec_1ee230(r0, p1));
    return r1;
}
