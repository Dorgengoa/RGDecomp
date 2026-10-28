/* rgp:protos */
#define RGP_SELF_IpuSkip32Bits_110160 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

/*rgp*/

s32 IpuSkip32Bits_110160(s32 a4)
{
    return (IpuSkipBitsThunk2_10de00(a4, 0x20), (s32)0);
}
