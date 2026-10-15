#include "types.h"

class VE {
    u8 pad_[0x50];
public:
    virtual void vs0();
    virtual void vs1();
    virtual void vs2();
    virtual void vs3();
    virtual void vs4();
    virtual void vs5();
    virtual void vs6();
    virtual void vs7();
    virtual s32 f28(void *);
};

/* Rebuild.  The node init block is NOT dead-store-eliminated against the copy
   that follows because the stores go through a pointer mwcc cannot
   disambiguate - they are plain sequential statements.
   The inner array-grow loop is a `for` (retail's entry `b` carries the init in
   its delay slot).  Indirect call: table at 0x50, slot 0x28. */


extern "C" s32 MemStackHeapAlloc_14db10(void *, s32, s32, s32);
extern "C" void ModelMeshBuildFromResMaybe_15b7c0(void *, s32, void *, s32);
extern "C" void MemStackAllocQw_14d950(void *, s32);
extern "C" void *MemStackNew_14e230(s32, void *);
extern "C" void *MemStackNew_14e1b0(s32, void *);
extern "C" void MemStackReturnToOwnerMaybe_14dad0(void *);
extern "C" void MemStackHeapFree_14dcb0(void *, s32);

extern "C" s32 ModelMeshLinksBuildFromResMaybe_15af00(u8 *self, s32 a1, u8 *heap, void *a3)
{
    s32 h;
    s32 cnt;
    u8 *p;
    u8 *prev;
    u8 *q;
    s32 n;
    s32 *t;
    s32 i;

    h = MemStackHeapAlloc_14db10(a3, 2, 0, 0x40);
    ModelMeshBuildFromResMaybe_15b7c0(self, a1, a3, 0);
    cnt = ((VE *)self)->f28( *(u8 **)(heap + 0x28) + (*(s32 *)(heap + 0x2C) << 4));
    if (cnt > 0) {
        MemStackAllocQw_14d950(heap, cnt);
    }
    p = *(u8 **)(self + 0xF0);
    prev = 0;
    while (p != 0) {
        q = (u8 *)MemStackNew_14e230(0x14, heap);
        if (q == 0) {
            break;
        }
        *(s32 *)(q + 0x00) = 0;
        *(s32 *)(q + 0x04) = 0;
        *(s32 *)(q + 0x0C) = -1;
        *(s32 *)(q + 0x08) = 0;
        *(s32 *)(q + 0x10) = 0;
        *(s32 *)(q + 0x04) = *(s32 *)(p + 0x04);
        *(s32 *)(q + 0x08) = *(s32 *)(p + 0x08);
        *(s32 *)(q + 0x0C) = *(s32 *)(p + 0x0C);
        *(s32 *)(q + 0x10) = *(s32 *)(p + 0x10);
        *(s32 *)(q + 0x04) = 0;
        if (prev == 0) {
            *(u8 **)(self + 0x130) = q;
        } else {
            *(u8 **)(prev + 0x0) = q;
        }
        p = *(u8 **)(p + 0x0);
        prev = q;
    }
    n = *(s32 *)(self + 0x128);
    if (n > 0 && *(s32 **)(self + 0x12C) != 0) {
        t = (s32 *)MemStackNew_14e1b0(n * 4, heap);
        if (t != 0) {
            for (i = 0; i < *(s32 *)(self + 0x128); i++) {
                t[i] = (*(s32 **)(self + 0x12C))[i];
            }
        }
        *(s32 **)(self + 0x12C) = t;
    } else {
        *(s32 *)(self + 0x128) = 0;
        *(s32 *)(self + 0x12C) = 0;
    }
    *(s32 *)(self + 0xB0) = 0;
    *(s32 *)(self + 0xB4) = 0;
    *(s32 *)(self + 0xB8) = 0;
    *(s32 *)(self + 0xBC) = 0;
    *(s32 *)(self + 0xC0) = 0;
    *(s32 *)(self + 0xC4) = 0;
    *(s32 *)(self + 0xC8) = 0;
    *(s32 *)(self + 0xCC) = 0;
    *(s32 *)(self + 0xD0) = 0;
    *(s32 *)(self + 0xD4) = 0;
    *(s32 *)(self + 0xD8) = 0;
    *(s32 *)(self + 0xDC) = 0;
    *(s32 *)(self + 0xE0) = 0;
    *(s32 *)(self + 0xF0) = 0;
    MemStackReturnToOwnerMaybe_14dad0(a3);
    MemStackHeapFree_14dcb0(a3, h);
    return 1;
}
