/* rgp:protos */
#define RGP_SELF_MesWinSetTextWithEnd_2726c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

/*rgp*/

s32 MesWinSetTextWithEnd_2726c0(s32 a4, s32 a5, s32 a6)
{
    return (MesWinSetText_2727b0(a4, a5, a6, 1), (s32)0);
}
