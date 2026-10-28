/* rgp:protos */
#define RGP_SELF_AiCmdFieldHudGetSuggestMember_2caa60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 AiCmdFieldHudGetSuggestMember_2caa60(s32 p0)
{
    s32 r0;
    s32 r1;

    r0 = FieldHudGetSuggestMember_203c20();
    r1 = (ScriptSlotStoreIntRef_2cc900(p0, r0), (s32)0);
    return 1;
}
