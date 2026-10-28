#include "types.h"
/* stack-block, 2026-10-19 (docs/PROTOS.md "Stack-block census"):
   - trailing pad: CopyHandle_401680 stores a 20-byte handle into `s32 h[4]`
     (ScriptCmdEffectGetParamFloat_32d940 / EffectCopyHandle_2dd3b0 shape): the
     slot past h is written by the callee, so the block is built and padded;
   - switch callee: SwitchReach_4016c0 reaches k[3] only in a jump-table case
     (VariantGetS16_36fcc0 shape): `s32 k[2]` + `s32 j` are one block;
   - LEN_ARG: memcpy(&t, .., 4) reaches 4 bytes, not memcpy's unroll width */
extern void CopyHandle_401680(s32 *h);
extern void SwitchReach_4016c0(s32 *k);
extern void *memcpy(void *d, const void *s, u32 n);

s32 PadBlock_401600(s32 *src)
{
    s32 k[2];
    s32 j[2];
    s32 h[4];
    s32 t;
    s32 u;

    CopyHandle_401680(h);
    SwitchReach_4016c0(k);
    memcpy(&t, src, 4);
    j[0] = 0;
    return h[0] + k[0] + t + j[0];
}
