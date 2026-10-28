/* rgp:protos */
#define RGP_SELF_HandleHeapPoolAlloc_312880 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

typedef struct Obj5_FUN_00312880 {
    s32 m00;         /* +0x0 */
} Obj5_FUN_00312880;

/*rgp*/

s32 HandleHeapPoolAlloc_312880(s32 a4, Obj5_FUN_00312880 *o, s32 a6)
{
    return (HandleHeapAlloc_312bf0(a4, o->m00, a6), (s32)0);
}
