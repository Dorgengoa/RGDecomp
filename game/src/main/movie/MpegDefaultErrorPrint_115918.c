/* rgp:protos */
#define RGP_SELF_MpegDefaultErrorPrint_115918 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */
/* The callee scans as VARARGS (reads $a2..$t3 unwritten); the arg
   count here is only what this stub itself marshals. */

extern u8 D_00456660[];

extern s32 scePrintf_119288(void *, s32);

s32 MpegDefaultErrorPrint_115918(s32 a4)
{
    return scePrintf_119288(D_00456660, a4);
}
