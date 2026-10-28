/* rgp:protos */
#define RGP_SELF_ModelObjUpdateMotions_1add20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void ModelObjUpdateMotions_1add20(s32 p0, f32 fa0)
{
    MotionListUpdateAll_171e40((p0 + 0x1F0), fa0);
    ModelObjSyncShadowModelFrames_1adbc0(p0);
}
