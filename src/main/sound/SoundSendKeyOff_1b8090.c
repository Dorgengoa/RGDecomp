#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */
/* The callee scans as VARARGS (reads $a2..$t3 unwritten); the arg
   count here is only what this stub itself marshals. */

extern s32 SoundSendCmd_1b6cc0(s32, s32, s32, s32, s32, s32, s32, s32);

s32 SoundSendKeyOff_1b8090(s32 a4, s32 a5, s32 a6, s32 a7, s32 a8)
{
    return SoundSendCmd_1b6cc0(0x1B, 6, a4, a8, a5, a6, 0, a7);
}
