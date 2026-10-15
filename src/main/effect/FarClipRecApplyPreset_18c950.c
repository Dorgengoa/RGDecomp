#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 FarClipRecGetPresetFadeRates_186e70(s32, void *, void *);

s32 FarClipRecApplyPreset_18c950(void *p4, s32 a5)
{
    return FarClipRecGetPresetFadeRates_186e70(a5, (u8 *)p4 + 0x1C, (u8 *)p4 + 0x20);
}
