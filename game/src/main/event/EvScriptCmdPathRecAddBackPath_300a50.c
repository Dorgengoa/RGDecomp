/* rgp:protos */
#define RGP_SELF_EvScriptCmdPathRecAddBackPath_300a50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern u8 D_00462100[];

/*rgp*/

s32 EvScriptCmdPathRecAddBackPath_300a50(s32 a4, s32 a5)
{
    return EventPathTemplateAddPath_300b90(a4, a5, D_00462100);
}
