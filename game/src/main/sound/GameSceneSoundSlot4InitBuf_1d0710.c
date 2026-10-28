/* rgp:protos */
#define RGP_SELF_GameSceneSoundSlot4InitBuf_1d0710 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

/*rgp*/

s32 GameSceneSoundSlot4InitBuf_1d0710(void *p4, s32 a5, s32 a6, s32 a7)
{
    return (SoundSlotInitBuf_1d2070((u8 *)p4 + 0xB2D0, a5, a6, a7), (s32)0);
}
