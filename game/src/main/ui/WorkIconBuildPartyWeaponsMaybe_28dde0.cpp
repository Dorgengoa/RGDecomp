#include "types.h"

typedef struct Elem2_0028DDE0 {
    u8 pad0[0x2C];
    s16 unk2C;
} Elem2_0028DDE0;

typedef struct Elem0028DDE0 {
    u8 pad0[0x10];
    Elem2_0028DDE0 *unk10;
} Elem0028DDE0;

class Obj0028DDE0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    Elem0028DDE0 * get390() { return VCM0(Elem0028DDE0 *, 0x390); }
};

typedef struct Ctx0028DDE0 {
    u8 pad0[0x18];
    s32 unk18;
} Ctx0028DDE0;

typedef struct Rect0028DDE0 {
    s32 x;
    s32 y;
    s32 w;
    s32 h;
} Rect0028DDE0;

extern "C" {
void GetDrawCtxNameTable_15de40();
Ctx0028DDE0 *GetGameData_1fede0();
void WorkIconCopyItemIcon_28df20(Rect0028DDE0 *, s16);
Elem2_0028DDE0 *CharaGetIconRecMaybe_3ae3e0(Obj0028DDE0 *);
s32 PartyCountReserve_3c1c20(s32, s32, s32);
s32 PartyCountMembers_3c2010(s32, s32, s32);
Obj0028DDE0 *PartyGetSlotChara_3c2fb0(s32, s32);
s32 WorkIconBuildPartyWeaponsMaybe_28dde0(void);
}

s32 WorkIconBuildPartyWeaponsMaybe_28dde0(void)
{
    Rect0028DDE0 r __attribute__((aligned(16)));
    Ctx0028DDE0 *ctx;
    Obj0028DDE0 *obj;
    Elem0028DDE0 *e;
    Elem2_0028DDE0 *e2;
    s32 n;
    s32 i;
    s32 x;

    ctx = GetGameData_1fede0();
    if (ctx == 0) {
        return 1;
    }
    n = ctx->unk18;
    n = PartyCountMembers_3c2010(n, 1, 1) + PartyCountReserve_3c1c20(n, 1, 1);
    for (i = 0; i < n; i++) {
        obj = PartyGetSlotChara_3c2fb0(ctx->unk18, i);
        if (obj == 0) {
            return 2;
        }
        e = obj->get390();
        if (e != 0) {
            GetDrawCtxNameTable_15de40();
            e2 = CharaGetIconRecMaybe_3ae3e0(obj);
            if (e2 != 0) {
                Elem2_0028DDE0 *q = e->unk10;
                s16 k;
                x = e2->unk2C;
                k = q->unk2C;
                r.x = (x % 8) << 5;
                r.y = (x / 8) << 5;
                r.w = 0x20;
                r.h = 0x20;
                WorkIconCopyItemIcon_28df20(&r, k);
            }
        }
    }
    return 0;
}
