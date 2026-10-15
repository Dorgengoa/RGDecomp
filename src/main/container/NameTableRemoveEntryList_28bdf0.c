#include "types.h"

extern s32 GetDrawCtxNameTable_15de40(void);
extern void NameTableRemoveByName_158c40(s32, void *, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x8];
    s32 m08;
};

void NameTableRemoveEntryList_28bdf0(struct Obj0 *p0, s32 p1)
{
    s32 r0;
    struct Obj0 * l1;
    s32 l2;

    if (p0 != 0) {
        r0 = GetDrawCtxNameTable_15de40();
        l1 = (struct Obj0 *)((u8 *)p0 + 0x10);
        l2 = 0;
        while ((u32)l2 < (u32)p0->m08) {
            NameTableRemoveByName_158c40(r0, l1, p1);
            l2 = (l2 + 1);
            l1 = (struct Obj0 *)((u8 *)l1 + 0x40);
        }
    }
}
