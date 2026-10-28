/* rgp:protos */
#define RGP_SELF_CharaResReleaseAllMon_1f1060 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

/*rgp*/

s32 CharaResReleaseAllMon_1f1060(s32 a4, s32 a5)
{
    return (CharaResReleaseByKind_1f1080(a4, a5, 2), (s32)0);
}
