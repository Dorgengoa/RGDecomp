/* rgp:protos */
#define RGP_SELF_EvCmdMenuHelpResReady_25bd10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Known-positive sibling shape of EvCmdMenuHelpIsOpen_25bcd0 (byte-identical, in cunits). */

/*rgp*/
/*rgp*/

s32 EvCmdMenuHelpResReady_25bd10(s32 p0)
{
    s32 r0;
    s32 r1;

    r0 = ((unsigned char)HelpMenuResReady_2032b0());
    r1 = (ScriptSetRefInt_26a1e0(p0, (r0 & 0xFF)), (s32)0);
    return 1;
}
