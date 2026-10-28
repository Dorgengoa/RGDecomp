/* rgp:protos */
#define RGP_SELF_EvCmdSceneOverlayModeSet_25bc80 1
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

s32 EvCmdSceneOverlayModeSet_25bc80(s32 p0)
{
    s32 r0;
    s32 rv3;
    s32 r1;
    s32 r2;

    r0 = ScriptGetInt_26a2a0(p0);
    rv3 = r2;
    if (r0 == 1) {
        r1 = (SceneOverlayModeOn_288340(), (s32)0);
        rv3 = r1;
    } else {
        r2 = (SceneOverlayModeOff_288300(), (s32)0);
        rv3 = r2;
    }
    return 1;
}
