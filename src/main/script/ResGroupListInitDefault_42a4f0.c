#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 ResGroupListInit_42a390(s32, s32, s32, s32, s32, s32);

s32 ResGroupListInitDefault_42a4f0(s32 a4)
{
    return ResGroupListInit_42a390(a4, 0, -1, 0, 0, 0);
}
