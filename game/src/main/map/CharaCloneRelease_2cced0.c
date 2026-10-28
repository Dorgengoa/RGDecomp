/* rgp:protos */
#define RGP_SELF_CharaCloneRelease_2cced0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_0047EDD0;
extern s32 D_0047EDD4;
extern s32 D_004825D8;

void CharaCloneRelease_2cced0(s32 p0)
{
    GameSceneObjReleaseMaybe_1cfc50(p0, 0x9C);
    D_004825D8 = 0;
    D_0047EDD0 = -1;
    D_0047EDD4 = -1;
}
