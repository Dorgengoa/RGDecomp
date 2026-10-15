#include "types.h"

extern s32 GetDrawCtxNameTable_15de40(void);
extern void NameTableFreeGroup_158ac0(s32, s32);
extern void MemStackHeapFree_14dcb0(s32, s32);
extern void LoaderReleaseHandle_1ccb70(void *);
extern void InsectCageSlotReset_39bb10(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s32 m00;
    s32 m04;
    u8 pad008[0x10];
    s32 m18;
    u8 pad01C[0x4];
    s32 m20;
};

void InsectCageSlotRelease_39b9c0(struct Obj0 *p0)
{
    s32 t0;
    s32 r0;
    s32 t1;
    s32 t2;
    s32 t3;

    t0 = p0->m18;
    if (t0 != 0) {
        r0 = GetDrawCtxNameTable_15de40();
        t1 = p0->m20;
        NameTableFreeGroup_158ac0(r0, t1);
        t2 = p0->m04;
        if (t2 != 0) {
            t3 = p0->m00;
            MemStackHeapFree_14dcb0(t2, t3);
        }
    }
    LoaderReleaseHandle_1ccb70((struct Obj0 *)((u8 *)p0 + 8));
    InsectCageSlotReset_39bb10(p0);
}
