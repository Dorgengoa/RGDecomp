/* rgp:protos */
#define RGP_SELF_TextEntryDialogInputStateThunk_4327b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00484104;

s32 TextEntryDialogInputStateThunk_4327b0(s32 p0, s32 p1)
{
    s32 t0;

    t0 = D_00484104;
    if (t0 != 0) {
        TextEntryDialogInputState_433090(t0, p1);
    }
    return 1;
}
