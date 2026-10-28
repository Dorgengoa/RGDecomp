/* rgp:protos */
#define RGP_SELF_FieldViewModeRestart_2d1420 1
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
    u8 pad000[0xD0];
    s32 mD0;
};

void FieldViewModeRestart_2d1420(struct Obj0 *p0)
{
    s32 t0;

    if (p0 != 0) {
        t0 = p0->mD0;
        if ((t0 & 0x400) == 0) {
            return;
        }
        FieldViewModeLeave_2f3660(0xFFFF, 1);
        FieldViewModeEnter_2f35e0();
    }
}
