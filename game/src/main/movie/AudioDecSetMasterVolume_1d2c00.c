/* rgp:protos */
#define RGP_SELF_AudioDecSetMasterVolume_1d2c00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */
/* The callee scans as VARARGS (reads $a2..$t3 unwritten); the arg
   count here is only what this stub itself marshals. */

/*rgp*/

s32 AudioDecSetMasterVolume_1d2c00(s32 a4)
{
    return SoundSendCmd_1b6cc0(0xC, 2, a4, a4);
}
