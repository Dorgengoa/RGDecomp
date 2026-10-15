#include "types.h"

/* Asymmetric guard pair over 0x20 records of 0x10 bytes, answering "is this
   slot empty?".  Retail's `beql` carries the 1 in its own delay slot, which
   is the one-instruction-else shape -- so the source tests `== 0` and returns
   1 inside the guard rather than inverting it.

   EventCastSetFloatStubMaybe_257cd0 and EventCastSetFloatStubMaybe_257d10 are byte-identical bodies at two addresses. */

typedef struct Rec10 {
    s32 f0;            /* +0x00 */
    s32 unk4;
    s32 unk8;
    s32 unkC;
} Rec10;

s32 EventCastSetFloatStubMaybe_257d10(Rec10 *rec, s32 index)
{
    u8 ok;

    if (index < 0) {
        goto none;
    }
    ok = index < 0x20;
    if (ok != 0) {
        goto found;
    }
none:
    return 0;
found:
    if (rec[index].f0 == 0) {
        goto yes;
    }
    return 0;
yes:
    return 1;
}
