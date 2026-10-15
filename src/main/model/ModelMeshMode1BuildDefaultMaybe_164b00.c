#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 ModelMeshMode1BuildFromResMaybe_164770(s32, s32, s32, s32);

s32 ModelMeshMode1BuildDefaultMaybe_164b00(s32 a4, s32 a5, s32 a6)
{
    return ModelMeshMode1BuildFromResMaybe_164770(a4, a5, a6, 1);
}
