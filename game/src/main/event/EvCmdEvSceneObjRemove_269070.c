/* rgp:protos */
#define RGP_SELF_EvCmdEvSceneObjRemove_269070 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void EvCmdEvSceneObjRemove_269070(s32 p0)
{
    s32 r0;

    r0 = ScriptGetInt_26a2a0(p0);
    EvSceneObjRemove_2690a0(r0);
}
