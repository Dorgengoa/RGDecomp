/* rgp:protos */
#define RGP_SELF_EvCmdSoundBankFree_261bc0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Known-positive sibling shape of EvCmdEventObjMgrResolveAndResetAll_2403f0 (byte-identical, in cunits). */

/*rgp*/
/*rgp*/

s32 EvCmdSoundBankFree_261bc0(void *rgp_a0)
{
    s32 r0;
    s32 r1;

    r0 = ScriptGetInt_26a2a0((void *)rgp_a0);
    r1 = (SoundBankFree_1b9c00(r0), (s32)0);
    return 1;
}
