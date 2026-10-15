#include "types.h"

extern s32 GetEntryTableGlobal_32c2e0(void);
extern s32 VariantGetInt_15f780(s32);
extern s32 EntryListSelectByIndex_323540(s32, s32);
extern void * EntryTableGetCurrent_323530(s32);
extern s32 EntryListGetTileSize_3237b0(s32);
extern s32 EntrySetTileSize_323ae0(void *, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x2C];
    s32 m2C;
};

s32 EntryScriptCmdSelectEntry_322f90(s32 p0)
{
    s32 r0;
    s32 rv7;
    s32 r1;
    s32 r2;
    struct Obj0 *r3;
    s32 rv6;
    s32 r4;
    s32 r5;

    r0 = GetEntryTableGlobal_32c2e0();
    rv7 = rv6;
    if (r0 == 0) {
        rv7 = 0;
    } else {
        r1 = VariantGetInt_15f780(p0);
        r2 = EntryListSelectByIndex_323540(r0, r1);
        r3 = EntryTableGetCurrent_323530(r0);
        rv6 = 1;
        if (r3 == 0) {
            rv6 = 0;
        } else {
            r3->m2C = r1;
            r4 = EntryListGetTileSize_3237b0(r0);
            r5 = EntrySetTileSize_323ae0(r3, r4);
            rv6 = 1;
        }
        rv7 = rv6;
    }
    return rv7;
}
