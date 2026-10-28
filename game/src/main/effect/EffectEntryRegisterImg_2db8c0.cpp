#include "types.h"
#pragma opt_common_subs off
#pragma opt_propagation off

#define P(p, o) (*(void **)((u8 *)(p) + (o)))
#define I(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define H(p, o) (*(s16 *)((u8 *)(p) + (o)))
static inline bool has(void *p) { return I(p, 0x28) != 0; }

extern "C" {
extern s32 MemStackAllocAligned64_14da10(void *arg0, s32 arg1);
extern void MemStackReturnToOwnerMaybe_14dad0(void *arg0);
extern s32 MemStackHeapAlloc_14db10(void *arg0, s32 arg1, u32 arg2, s32 arg3);
extern void NameTableRegisterImArchive_1594d0(s32 arg0, s32 arg1, s32 arg2, void *arg3, s32 arg4);
extern s32 GetDrawCtxNameTable_15de40(void);
extern s32 GetEffectMgr_2d9040(void);
extern void memcpy(s32 arg0, s32 arg1, u32 arg2);
}

extern "C" s32 EffectEntryRegisterImg_2db8c0(void *arg0, s32 arg1, s32 arg2)
{
    void *p;
    bool flag;
    s32 r;
    s32 h;
    s32 n;
    s32 a1;

    if (GetEffectMgr_2d9040() == 0) {
        return 1;
    }
    p = P(arg0, 0xA4);
    flag = !has(p);
    if (flag) {
        I(arg0, 0x84) = MemStackHeapAlloc_14db10(p, 3, ((arg2 & 0xF) ? ((u32)arg2 >> 4) + 1 : (u32)arg2 >> 4), 0x40);
    } else {
        I(arg0, 0x84) = 0;
    }
    p = P(arg0, 0xA4);
    if (I(p, 0x34) - I(p, 0x2C) < arg2 / 16 + 1) {
        if (flag) {
            MemStackReturnToOwnerMaybe_14dad0(p);
        }
        return 1;
    }
    n = arg2 / 16 + 1;
    I(arg0, 0x9C) = n;
    r = MemStackAllocAligned64_14da10(P(arg0, 0xA4), n);
    I(arg0, 0x84) = r;
    if (r == 0) {
        return 1;
    }
    h = GetDrawCtxNameTable_15de40();
    a1 = arg1;
    memcpy(I(arg0, 0x84), a1, arg2);
    NameTableRegisterImArchive_1594d0(h, I(arg0, 0x84), H(arg0, 0x14), P(arg0, 0xA4), 0);
    if (flag) {
        MemStackReturnToOwnerMaybe_14dad0(P(arg0, 0xA4));
    }
    H(arg0, 0xB4) |= 1;
    return 0;
}
