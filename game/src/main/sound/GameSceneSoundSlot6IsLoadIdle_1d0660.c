/* rgp:protos */
#define RGP_SELF_GameSceneSoundSlot6IsLoadIdle_1d0660 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

/*rgp*/

s32 GameSceneSoundSlot6IsLoadIdle_1d0660(void *p4)
{
    return ((unsigned char)SoundSlotIsLoadIdle_1d1d50((u8 *)p4 + 0xB3E0));
}
