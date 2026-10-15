#include "types.h"

extern void EntryListSetTileSize_3237c0(void *, s32);
extern void EntryListSetChildCount_3237a0(void *, s32);
extern void EntryListSetKind_3236b0(void *, s32);
extern void EntryListSetCount_3236a0(void *, s32);
extern void EntryListSetCurIndex_3238c0(void *, s32);
extern void EntryListSetChildCursor_3233b0(void *, s32);
extern void EntryListSetCellCursor_323380(void *, s32);
extern void EntryListSetTexSize_323350(void *, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x4];
    s32 m04;
    s32 m08;
    s32 m0C;
    s32 m10;
};

void EntryListReset_3237f0(struct Obj0 *p0)
{
    EntryListSetTileSize_3237c0(p0, 0);
    EntryListSetChildCount_3237a0(p0, 0);
    EntryListSetKind_3236b0(p0, 0);
    EntryListSetCount_3236a0(p0, 0);
    p0->m04 = 0;
    p0->m08 = 0;
    p0->m0C = 0;
    EntryListSetCurIndex_3238c0(p0, 0);
    EntryListSetChildCursor_3233b0(p0, 0);
    EntryListSetCellCursor_323380(p0, 0);
    EntryListSetTexSize_323350(p0, 0, 0);
    p0->m10 = 0;
}
