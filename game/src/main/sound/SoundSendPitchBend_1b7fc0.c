/* rgp:protos */
#define RGP_SELF_SoundSendPitchBend_1b7fc0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */
/* The callee scans as VARARGS (reads $a2..$t3 unwritten); the arg
   count here is only what this stub itself marshals. */

/*rgp*/

s32 SoundSendPitchBend_1b7fc0(s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9)
{
    return SoundSendCmd_1b6cc0(0x1F, 5, a4, a9, 0, a7, a8);
}
