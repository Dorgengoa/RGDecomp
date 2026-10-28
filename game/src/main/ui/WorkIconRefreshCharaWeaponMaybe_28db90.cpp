#include "types.h"

struct O28db90 {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void * f390() { return VCM0(void *, 0x390); }
};

extern "C" {
void *GetGameData_1fede0(void);
O28db90 *PartyFindCharaById_3c2ed0(s32, s32);
void GetDrawCtxNameTable_15de40(void);
void *CharaGetIconRecMaybe_3ae3e0(O28db90 *);
void WorkIconCopyCharaItemIcon_28dc80(s32 *, s32, s32);
}

extern "C" s32 WorkIconRefreshCharaWeaponMaybe_28db90(s32 arg0)
{
    void *top;
    O28db90 *o;
    void *r;
    void *q;
    s16 a;
    s32 b;
    s32 rc[4] __attribute__((aligned(16)));

    top = GetGameData_1fede0();
    if (top == 0) {
        return 1;
    }
    o = PartyFindCharaById_3c2ed0(*(s32 *)((u8 *)top + 0x18), arg0);
    if (o == 0) {
        return 2;
    }
    r = o->f390();
    if (r != 0) {
        GetDrawCtxNameTable_15de40();
        q = CharaGetIconRecMaybe_3ae3e0(o);
        if (q == 0) {
            return 1;
        }
        b = *(s16 *)(*(u8 **)((u8 *)r + 0x10) + 0x2E);
    a = *(s16 *)((u8 *)q + 0x2C);
        rc[0] = (a % 8) << 5;
        rc[1] = (a / 8) << 5;
        rc[2] = 0x20;
        rc[3] = 0x20;
        WorkIconCopyCharaItemIcon_28dc80(rc, b, arg0);
    }
    return 0;
}
