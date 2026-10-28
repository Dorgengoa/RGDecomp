/* rgp:protos */
#define RGP_SELF_CharaAddReqMove_238730 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

/*rgp*/

s32 CharaAddReqMove_238730(void *p4, s32 a5)
{
    return (VecAdd_1cbdc0((u8 *)p4 + 0xD0, (u8 *)p4 + 0xD0, a5), (s32)0);
}
