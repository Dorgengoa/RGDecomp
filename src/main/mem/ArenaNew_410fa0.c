#include "types.h"

/* Tail-call adapter: marshal and forward a global address. */

extern s32 ArenaAllocAligned_370330(s32, s32);

s32 ArenaNew_410fa0(s32 a4, s32 a5)
{
    return ArenaAllocAligned_370330(a5, a4);
}
