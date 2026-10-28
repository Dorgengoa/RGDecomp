/* rgp:protos */
#define RGP_SELF_StreamChanSaveResumePoint_1d6b00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

/*rgp*/

s32 StreamChanSaveResumePoint_1d6b00(s32 a4)
{
    return (StreamChanSetSaveResumeReq_1d70b0(a4, 1), (s32)0);
}
