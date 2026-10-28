/* rgp:protos */
#define RGP_SELF_AiCmdGetSelfId_2c80d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_004DB928;
extern s32 D_004DB92C;

s32 AiCmdGetSelfId_2c80d0(s32 p0, s32 p1)
{
    s32 rv2;
    s32 t0;
    s32 rv1;
    s32 t1;
    s32 r0;

    rv2 = rv1;
    if (p1 != 1) {
        rv2 = 0;
    } else {
        t0 = D_004DB92C;
        rv1 = 1;
        if (t0 == 0) {
            rv1 = 0;
        } else {
            t1 = D_004DB928;
            r0 = (ScriptSlotStoreIntRef_2cc900(p0, t1), (s32)0);
            rv1 = 1;
        }
        rv2 = rv1;
    }
    return rv2;
}
