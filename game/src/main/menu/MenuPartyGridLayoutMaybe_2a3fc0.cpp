/* rgp:protos */
#line 1
#include "types.h"
#pragma optimization_level 3


struct R32 {
    s16 f0;
    s16 f2;
    s16 f4;
    s16 f6;
    s16 f8;
    s16 fA;
    s16 fC;
    s16 fE;
    s32 pad[4];
};

struct E6 {
    s16 key;
    s16 a;
    s16 b;
};

class VO {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    u8 * v244() { return VCM0(u8 *, 0x3D8); }
};

extern "C" {
R32 *UiGetWidgetSprite_28fe10(s32, s32, s32);
u8 *GetGameData_1fede0(void);
s32 PartyCountMembers_3c2010(s32, s32, s32);
s32 PartyCountReserve_3c1c20(s32, s32, s32);
VO * PartyGetSlotChara_3c2fb0(s32, s32);
u8 *CharaGetIconRecMaybe_3ae3e0(VO *);
void UiSetSpriteUv_28f970(s32, s32, s32, s32, s32);
void UiSetItemIconUv_288e50(R32 *, s32, s32, s32);
extern E6 D_00450D30[];
extern E6 D_00450D80[];
}

extern "C" s32 MenuPartyGridLayoutMaybe_2a3fc0(s32 *arg0)
{
    R32 *r0;
    R32 *r1;
    R32 *r2;
    R32 *r3;
    R32 *r4;
    u8 *g;
    s32 t;
    s32 sel;
    s32 i;
    s32 m;
    s32 d;
    s32 j;
    s32 key;
    VO *o;
    u8 *p;
    R32 *q;

    r0 = UiGetWidgetSprite_28fe10(*arg0, 0xB1, 0);
    if (r0 == 0) {
        return 0;
    }
    r1 = UiGetWidgetSprite_28fe10(*arg0, 0xB3, 0);
    if (r1 == 0) {
        return 0;
    }
    r2 = UiGetWidgetSprite_28fe10(*arg0, 0xB2, 0);
    if (r2 == 0) {
        return 0;
    }
    r3 = UiGetWidgetSprite_28fe10(*arg0, 0xAF, 0);
    if (r3 == 0) {
        return 0;
    }
    r4 = UiGetWidgetSprite_28fe10(*arg0, 0xB0, 0);
    if (r4 == 0) {
        return 0;
    }
    g = GetGameData_1fede0();
    t = *(s32 *)(g + 0x18);
    sel = PartyCountMembers_3c2010(t, 1, 1) + PartyCountReserve_3c1c20(t, 1, 1);
    for (i = 0; i < 8; i++) {
        if (i == sel) {
            q = &r2[i];
            r4[i].f0 = -1;
            r3[i].f0 = -1;
            q->f0 = -1;
            q->f0 = -1;
            r1[i].f0 = -1;
            r0[i].f0 = -1;
            break;
        }
        m = (i % 4) * 97;
        d = (i / 4) * 97;
        r0[i].f0 = r1[i].f0 = r2[i].f0 = m + 0x18;
        r0[i].f2 = r1[i].f2 = d + 0x4C;
        r2[i].f2 = d + 0x38;
        r3[i].f0 = m + 0x4F;
        r3[i].f2 = d + 0x64;
        o = PartyGetSlotChara_3c2fb0(*(s32 *)(g + 0x18), i);
        if (o == 0) {
            return 0;
        }
        key = *(s16 *)(CharaGetIconRecMaybe_3ae3e0(o) + 0x2C);
        for (j = 0; j < 10; j++) {
            if (key == D_00450D30[j].key) {
                UiSetSpriteUv_28f970(*arg0, 0xB3, D_00450D30[j].a, D_00450D30[j].b, i);
                UiSetSpriteUv_28f970(*arg0, 0xB2, D_00450D80[j].a, D_00450D80[j].b, i);
                break;
            }
        }
        p = o->v244();
        if (p != 0) {
            UiSetItemIconUv_288e50(&r4[i], *(s16 *)(*(u8 **)(p + 0x10) + 0x2C), 0x28, 0x2D);
            r4[i].f0 = m + 0x4E;
            r4[i].f2 = d + 0x61;
        } else {
            r4[i].fE = 0;
            r4[i].f6 = 0;
            r4[i].fC = 0;
            r4[i].f4 = 0;
        }
    }
    return 1;
}
