/* rgp:protos */
#define RGP_SELF_FarClipRecApplyPreset_18c950 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

/*rgp*/

s32 FarClipRecApplyPreset_18c950(void *p4, s32 a5)
{
    return (FarClipRecGetPresetFadeRates_186e70(a5, (u8 *)p4 + 0x1C, (u8 *)p4 + 0x20), (s32)0);
}
