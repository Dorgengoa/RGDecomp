/* rgp:protos */
#define RGP_SELF_SoundPlayDefault_1b9ae0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

/*rgp*/

s32 SoundPlayDefault_1b9ae0(s32 a4, s32 a5, s32 a6)
{
    return (SoundPlayEntry_1b8f90(a4, a5, -1, -1, 0x40, 0x2000, a6), (s32)0);
}
