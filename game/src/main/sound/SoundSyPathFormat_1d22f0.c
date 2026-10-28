/* rgp:protos */
#define RGP_SELF_SoundSyPathFormat_1d22f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */
/* The callee scans as VARARGS (reads $a2..$t3 unwritten); the arg
   count here is only what this stub itself marshals. */

extern u8 D_0045B1A0[];

extern s32 Sprintf_1343b8(s32, void *, s32);

s32 SoundSyPathFormat_1d22f0(s32 a4, s32 a5)
{
    return Sprintf_1343b8(a4, D_0045B1A0, a5);
}
