#include "types.h"

typedef struct Self {
    u8 pad0[0x168];
    s32 heap;
} Self;

extern void **PoolAllocElem_36ab00(s32, s32, s32);
extern void InvObjVirtualReset_3d5120(void **);
extern u8 D_00471FE0[];
extern u8 D_004758D0[];
extern u8 D_004759F0[];
extern u8 D_00475B10[];
extern u8 D_00475CE0[];
extern u8 D_00475E00[];
extern u8 D_00475F20[];
extern u8 D_00476040[];
extern s32 D_00483894;

static inline void **Alloc(s32 heap, s32 sz) {
    if (heap == 0) {
        return 0;
    }
    return PoolAllocElem_36ab00(heap, sz, 0);
}

static inline void **New0(s32 heap) {
    void **o = (heap != 0) ? PoolAllocElem_36ab00(heap, 0x14, 0) : 0;
    if (o != 0) {
        *o = D_00471FE0;
        *o = D_00476040;
        InvObjVirtualReset_3d5120(o);
    }
    return o;
}

void **InvObjCreateByKind_3c75c0(Self *self, s32 kind) {
    s32 heap;
    void **p;

    if (kind < 0) {
        return 0;
    }
    heap = self->heap;
    if (heap == 0) {
        return 0;
    }
    if (D_00483894 == 0) {
        return 0;
    }
    p = 0;
    switch (kind) {
    case 0:
        p = New0(heap);
        break;
    case 1:
        if (heap != 0) {
            p = PoolAllocElem_36ab00(heap, 0x18, 0);
        }
        if (p != 0) {
            *p = D_00471FE0;
            *p = D_00476040;
            InvObjVirtualReset_3d5120(p);
            *p = D_00475F20;
            InvObjVirtualReset_3d5120(p);
        }
        break;
    case 2:
        if (heap != 0) {
            p = PoolAllocElem_36ab00(heap, 0x20, 0);
        }
        if (p != 0) {
            *p = D_00471FE0;
            *p = D_00476040;
            InvObjVirtualReset_3d5120(p);
            *p = D_00475E00;
            InvObjVirtualReset_3d5120(p);
        }
        break;
    case 3:
        if (heap != 0) {
            p = PoolAllocElem_36ab00(heap, 0x28, 0);
        }
        if (p != 0) {
            *p = D_00471FE0;
            *p = D_00476040;
            InvObjVirtualReset_3d5120(p);
            *p = D_00475E00;
            InvObjVirtualReset_3d5120(p);
            *p = D_00475CE0;
            InvObjVirtualReset_3d5120(p);
        }
        break;
    case 4:
        if (heap != 0) {
            p = PoolAllocElem_36ab00(heap, 0x1C, 0);
        }
        if (p != 0) {
            *p = D_00471FE0;
            *p = D_00476040;
            InvObjVirtualReset_3d5120(p);
            *p = D_00475B10;
            InvObjVirtualReset_3d5120(p);
        }
        break;
    case 5:
        if (heap != 0) {
            p = PoolAllocElem_36ab00(heap, 0x1C, 0);
        }
        if (p != 0) {
            *p = D_00471FE0;
            *p = D_00476040;
            InvObjVirtualReset_3d5120(p);
            *p = D_004759F0;
            InvObjVirtualReset_3d5120(p);
        }
        break;
    case 6:
        if (heap != 0) {
            p = PoolAllocElem_36ab00(heap, 0x1C, 0);
        }
        if (p != 0) {
            *p = D_00471FE0;
            *p = D_00476040;
            InvObjVirtualReset_3d5120(p);
            *p = D_004758D0;
            InvObjVirtualReset_3d5120(p);
        }
        break;
    }
    return p;
}
