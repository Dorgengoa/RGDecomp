#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 CharaResReleaseByKind_1f1080(s32, s32, s32);

s32 CharaResReleaseAllNpc_1f1070(s32 a4, s32 a5)
{
    return CharaResReleaseByKind_1f1080(a4, a5, 1);
}
