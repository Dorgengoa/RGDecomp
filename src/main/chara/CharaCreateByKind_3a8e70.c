#include "types.h"

extern void CharaKind1003Ctor_3a9050(void **);
extern void CharaKind1002Ctor_3a9090(void **);
extern void CharaBaseCtor_3a9190(void **);
extern void **PoolTryAllocElem_3afc20(s32, s32);
extern void UnitCtorReset_3b8a80(void **);
extern u8 D_004722A0[];
extern u8 D_004727B0[];
extern u8 D_00472CC0[];
extern u8 D_004731D0[];
extern u8 D_004736E0[];
extern s32 D_004837F0;

static inline void **NewA(s32 heap, s32 sz, u8 *vt) {
    void **p = PoolTryAllocElem_3afc20(sz, heap);
    if (p != 0) {
        CharaBaseCtor_3a9190(p);
        *p = vt;
    }
    return p;
}

static inline void **NewB(s32 heap, s32 sz, u8 *vt) {
    void **p = PoolTryAllocElem_3afc20(sz, heap);
    if (p != 0) {
        CharaKind1002Ctor_3a9090(p);
        *p = vt;
    }
    return p;
}

static inline void **NewC(s32 heap, s32 sz, u8 *vt) {
    void **p = PoolTryAllocElem_3afc20(sz, heap);
    if (p != 0) {
        CharaKind1003Ctor_3a9050(p);
        *p = vt;
    }
    return p;
}

void **CharaCreateByKind_3a8e70(void *arg0, s32 id)
{
    void **p;
    s32 heap;

    if (id < 0) {
        return 0;
    }
    if (D_004837F0 == 0) {
        goto fail;
    }
    heap = *(s32 *)((u8 *)arg0 + 8);
    if (heap == 0) {
    fail:
        return 0;
    }
    switch (id) {
    case 0x3E9:
        p = NewA(heap, 0x4C0, D_004736E0);
        break;
    case 0x3EA:
        p = NewA(heap, 0x4C0, D_004731D0);
        break;
    case 0x3EB:
        p = NewB(heap, 0x4C8, D_00472CC0);
        break;
    case 0x3EC:
        p = NewC(heap, 0x4C8, D_004727B0);
        break;
    case 0x3ED:
        p = NewB(heap, 0x4C0, D_004722A0);
        break;
    default:
        p = NewA(heap, 0x4C0, D_004731D0);
        break;
    }
    if (p == 0) {
        return 0;
    }
    UnitCtorReset_3b8a80(p);
    return p;
}
