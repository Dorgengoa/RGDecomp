/* rgp:protos */
#define RGP_SELF_GameSceneSoundSlot0PlaySe_1d05b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

/*rgp*/

s32 GameSceneSoundSlot0PlaySe_1d05b0(void *p4, s32 a5)
{
    return (SoundSlotPlaySe_1d1a50((u8 *)p4 + 0xB0B0, a5), (s32)0);
}
