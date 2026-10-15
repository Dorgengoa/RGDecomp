#include "types.h"

/* `beqz m34 -> shared return 0` then `bnez m38 -> body` is the short-circuit
   `||` shape, not two separate guards. */

extern void *SlotGetInt_15f720(void *);
extern void *VariantGetInt_15f780(void *);
extern void EffModelResGetVertex_1a81a0(void *, void *, void *);
extern void Vec4ArraySet_1a8760(void *, s32, void *);

s32 EffDefCmdEmitVertexId_19f1f0(u8 *args, s32 n, void **ctx)
{
    u8 *o = (u8 *)ctx[0];
    u8 tmp[16];

    if (*(void **)(o + 0x34) == 0 || *(void **)(o + 0x38) == 0) {
        return 0;
    }
    SlotGetInt_15f720(args);
    EffModelResGetVertex_1a81a0(*(void **)(o + 0x38), VariantGetInt_15f780(args + 8), tmp);
    Vec4ArraySet_1a8760(*(void **)(o + 0x34), *(s32 *)(o + 0x3C), tmp);
    *(s32 *)(o + 0x3C) = *(s32 *)(o + 0x3C) + 1;
    return 1;
}
