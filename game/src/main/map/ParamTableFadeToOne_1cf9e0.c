/* rgp:protos */
#define RGP_SELF_ParamTableFadeToOne_1cf9e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

/*rgp*/

s32 ParamTableFadeToOne_1cf9e0(s32 a4, s32 a5, s32 a6)
{
    return ((s32)ParamTableFadeTo_1cfa00(a4, a5, a6, 1.0f));
}
