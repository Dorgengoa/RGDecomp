/* rgp:protos */
#define RGP_SELF_GameSceneSoundNoteListInit_1d14e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

/*rgp*/

s32 GameSceneSoundNoteListInit_1d14e0(void *p4)
{
    return (SoundNoteListInit_1b4ee0((u8 *)p4 + 0xB0A4), (s32)0);
}
