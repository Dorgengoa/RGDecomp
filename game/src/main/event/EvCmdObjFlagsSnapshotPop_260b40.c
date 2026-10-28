/* rgp:protos */
#define RGP_SELF_EvCmdObjFlagsSnapshotPop_260b40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00481F78;

s32 EvCmdObjFlagsSnapshotPop_260b40(void)
{
    s32 r0;
    s32 r1;

    r0 = ((s32)GetObjRecFlagsSnapshotStack_1d7640());
    r1 = (ObjRecFlagsSnapshotPop_1d76a0(r0, D_00481F78), (s32)0);
    return 1;
}
