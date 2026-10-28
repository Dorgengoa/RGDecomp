/* rgp:protos */
#define RGP_SELF_EvCmdCameraBegin_2649a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00482060;
extern s32 D_004BD9A4;

s32 EvCmdCameraBegin_2649a0(void)
{
    s32 t0;
    s32 r0;
    s32 t1;
    s32 r1;

    t0 = D_00482060;
    r0 = (EventCameraReset_254a90(t0), (s32)0);
    t1 = D_004BD9A4;
    if (t1 == 0) {
        r1 = (CameraPushMode14_30a110(), (s32)0);
        *(s32 *)&D_004BD9A4 = 1;
    }
    return 1;
}
