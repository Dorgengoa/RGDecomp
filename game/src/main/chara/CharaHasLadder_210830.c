/* rgp:protos */
#define RGP_SELF_CharaHasLadder_210830 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* `sltu $2,$0,$2` then a branch, then `slt $2,$0,$2` with nothing to reset
   $2 on the failing path: a materialised `&&` of two truth tests. */
typedef struct P210830 { u8 pad000[0x858]; s32 m858; u8 pad85C[0x4]; u8 m860; } P210830;
s32 CharaHasLadder_210830(P210830 *p)
{
    return p->m860 != 0 && p->m858 > 0;
}
