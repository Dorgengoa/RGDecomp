/* EvMapNameRefCopy_367530 -- shape-identical to merged EvMapObjNodeCopy_3673f0 (29 instructions); the donor's
   source with the symbol renamed, 2 call target(s) and 1 immediate(s) substituted:
     EvMapObjNodeGetName_3673e0 -> EvMapNameRefGet_367520
     EvMapObjNodeReset_3674b0 -> EvMapNameRefReset_3675f0
     imm 320 -> 0
   Found by build/zz/s23_xclone.py. */
#include "types.h"

extern void EvMapNameRefReset_3675f0(void *);
extern s32 EvMapNameRefGet_367520(void *);
extern s32 MemStackStrDup_14cff0(s32, void *);

s32 EvMapNameRefCopy_367530(u8 *o, void *a, void *b)
{
    s32 r;

    EvMapNameRefReset_3675f0(o);
    if (a == 0 || b == 0) {
        return 0;
    }
    r = MemStackStrDup_14cff0(EvMapNameRefGet_367520(a), b);
    *(s32 *)(o + 0x0) = r;
    return r != 0;
}
