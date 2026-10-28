/* rgp:protos */
#define RGP_SELF_EffectReleaseNodesByKey_2e1250 1
#include "port/game_protos.h"
#line 1
/* EffectReleaseNodesByKey_2e1250 -- shape-identical to merged GsPktSetFrameMask_13e420 (2 instructions); the donor's
   source with the symbol renamed, 1 call target(s) and 1 immediate(s) substituted:
     GsFrameSetMaskMode_156cc0 -> EffectEntriesReleaseNodesByKey_2de590
     imm 16 -> 5748
   Found by build/zz/s23_xclone.py. */
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

/*rgp*/

s32 EffectReleaseNodesByKey_2e1250(void *p4, s32 a5, void *rgp_a2)
{
    return (EffectEntriesReleaseNodesByKey_2de590((u8 *)p4 + 0x1674, a5, (void *)rgp_a2), (s32)0);
}
