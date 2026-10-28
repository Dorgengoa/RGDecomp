#include "types.h"

struct V2a3d90 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f50() { return VCM0(s32, 0x50); }
};

struct E2a3d90 {
    u8 pad0[8];
    s64 m8;
    u8 pad10[0xC];
    s16 m1C;
    s16 m1E;
};

struct A2a3d90 {
    s32 m0;
    u8 pad4[0xD];
    s8 m11;
    u8 pad12[2];
    s32 m14;
    u8 pad18[8];
    s32 m20;
    s32 m24;
};

extern "C" {
u8 *GetGameData_1fede0(void);
E2a3d90 *UiGetWidgetSubItem_28f2b0(s32, s32, s32);
s32 MenuGetSelMode_2a4e10(A2a3d90 *);
s32 MenuGetMode_2a4e30(A2a3d90 *);
V2a3d90 *InvFindByInvId_3c87d0(s32, s32, s32);
s32 InvMakeIdFromCategory_3c88b0(s32, s32, s32, s32, s32);
s32 ItemHasCountFlag_3d44e0(V2a3d90 *);
extern s32 D_004659F0[4];
extern s32 D_004659F8[4];
}

extern "C" s32 MenuFillItemCounts_2a3d90(A2a3d90 *arg0, s32 arg1)
{
    E2a3d90 *e;
    s32 kind;
    u8 *top;
    s32 last;
    s32 i;
    s32 first;
    V2a3d90 *o;
    s32 v;

    e = UiGetWidgetSubItem_28f2b0(arg0->m0, arg1, 0);
    if (e == NULL) {
        return 0;
    }
    kind = arg0->m11;
    top = GetGameData_1fede0();
    first = InvMakeIdFromCategory_3c88b0(*(s32 *)(top + 0x18), arg0->m14, kind, 0, 0);
    last = InvMakeIdFromCategory_3c88b0(*(s32 *)(top + 0x18), arg0->m14, kind, D_004659F0[0] - 1, D_004659F8[0] - 1);
    for (i = first; i < last + 1; i++) {
        o = InvFindByInvId_3c87d0(*(s32 *)(top + 0x18), i, 0);
        e->m8 = e->m1C = e->m1E = 0;
        if (kind == arg0->m20 && i == first + arg0->m24 && MenuGetSelMode_2a4e10(arg0) == MenuGetMode_2a4e30(arg0)) {
            e++;
            continue;
        }
        if (o != NULL && ItemHasCountFlag_3d44e0(o) != 0) {
            v = o->f50();
            if (v > 1) {
                e->m8 = v;
                e->m1C = 10;
                e->m1E = 16;
            }
        }
        e++;
    }
    return 1;
}
