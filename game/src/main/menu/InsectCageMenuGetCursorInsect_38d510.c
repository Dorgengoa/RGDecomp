/* rgp:protos */
#define RGP_SELF_InsectCageMenuGetCursorInsect_38d510 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x96C];
    s32 m96C;
};

s32 InsectCageMenuGetCursorInsect_38d510(void)
{
    struct Obj0 *r0;
    s32 t0;

    r0 = InsectCageMenuGetCursorObjThunk_390f70();
    if (r0 != 0) {
        t0 = r0->m96C;
        return t0;
    }
    return 0;
}
