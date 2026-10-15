#include "types.h"

/* o->m20 is read into a named local BEFORE the VariantGetInt_15f780 call -- it is
   loaded in that call's delay slot, so it cannot be an argument expression
   evaluated at the Vec4ArrayAlloc_1a8710 call site. */

extern void *VariantGetInt_15f780(void *);
extern void Vec4ArrayAlloc_1a8710(void *, void *, void *);

s32 EffDefCmdEmitVertexNum_19f280(void *args, s32 n, void **ctx)
{
    u8 *o = (u8 *)ctx[0];
    void *w;
    void *v;

    w = *(void **)(o + 0x20);
    v = VariantGetInt_15f780(args);
    if (*(void **)(o + 0x34) != 0) {
        Vec4ArrayAlloc_1a8710(*(void **)(o + 0x34), v, w);
    }
    *(s32 *)(o + 0x3C) = 0;
    return 1;
}
