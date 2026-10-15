#include "types.h"

extern void EvMapObjNodeReset_3674b0(void *);
extern s32 EvMapObjNodeGetName_3673e0(void *);
extern s32 MemStackStrDup_14cff0(s32, void *);

s32 EvMapObjNodeCopy_3673f0(u8 *o, void *a, void *b)
{
    s32 r;

    EvMapObjNodeReset_3674b0(o);
    if (a == 0 || b == 0) {
        return 0;
    }
    r = MemStackStrDup_14cff0(EvMapObjNodeGetName_3673e0(a), b);
    *(s32 *)(o + 0x140) = r;
    return r != 0;
}
