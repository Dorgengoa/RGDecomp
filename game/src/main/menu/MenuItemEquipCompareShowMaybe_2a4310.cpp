#include "types.h"

class BV {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void set(void * a0) { VCM(void, (void *, void *), 0x4C, a0); }
};

class B : public BV {
public:
    u8 pad4[0xC];
    u8 *m10;
};

class A {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f60() { return VCM0(s32, 0x60); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    B * f388() { return VCM0(B *, 0x388); }
    B * f38C() { return VCM0(B *, 0x38C); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    B * f3C4() { return VCM0(B *, 0x3C4); }
};

extern "C" {
extern void Sprintf_1343b8(u8 *, s32, s32);
extern void UiSetItemIconUv_288e50(u8 *, s32, s32, s32);
extern s32 MsgTableLookup_28aa30(s32, s32);
extern void UiSetTextCenteredX_28f300(s32, s32, s32, s32);
extern s32 UiGetWidgetTextWidth_28f400(s32, s32, s32);
extern u8 *UiGetWidgetText_28f620(s32, s32, s32);
extern void UiSetSpriteX_28fcd0(s32, s32, s32, s32);
extern u8 *UiGetWidgetSprite_28fe10(s32, s32, s32);
extern u8 *CharaGetIconRecMaybe_3ae3e0(A *);
extern A *ItemFindOwnerChara_3d4d80(B *, s32);
extern s16 D_00450D30[];
extern s16 D_00450D32[];
extern s16 D_00450D34[];
extern s32 D_004823D8;
extern u8 D_004DB310[];
extern u8 D_004DB350[];
}

extern "C" s32 MenuItemEquipCompareShowMaybe_2a4310(u8 *arg0, B *arg1) {
    A *a;
    s32 id;
    u8 *w;
    u8 *m;
    B *b;
    s32 x;
    s32 y;
    s32 i;

    if (arg1 == 0) {
        return 0;
    }
    a = ItemFindOwnerChara_3d4d80(arg1, 1);
    if (a == 0) {
        return 0;
    }
    id = *(s16 *)(CharaGetIconRecMaybe_3ae3e0(a) + 0x2C);
    w = UiGetWidgetSprite_28fe10(*(s32 *)arg0, 0xAA, 0);
    if (w == 0) {
        return 0;
    }
    for (i = 0; i < 10; i++) {
        if (id == D_00450D30[i * 3]) {
            *(s16 *)(w + 0x8) = D_00450D32[i * 3];
            *(s16 *)(w + 0xA) = D_00450D34[i * 3];
            *(s16 *)(w + 0xC) = 0x36;
            *(s16 *)(w + 0x4) = 0x36;
            *(s16 *)(w + 0xE) = 0x42;
            *(s16 *)(w + 0x6) = 0x42;
            break;
        }
    }
    m = UiGetWidgetText_28f620(*(s32 *)arg0, 0xA6, 0);
    if (m == 0) {
        return 0;
    }
    Sprintf_1343b8(arg0 + 0x172, MsgTableLookup_28aa30(D_004823D8, 0x44E), a->f60());
    *(u8 **)(m + 4) = arg0 + 0x172;
    UiSetTextCenteredX_28f300(*(s32 *)arg0, 0xA6, 0x9D, 0);
    *(s16 *)m += 0x10;
    b = 0;
    x = *(s8 *)(arg1->m10 + 2);
    if (x == 0) {
        b = a->f388();
    } else if (x == 1) {
        b = a->f38C();
    } else if (x == 2) {
        b = a->f3C4();
    }
    if (b == 0) {
        return 0;
    }
    b->set(D_004DB310);
    arg1->set(D_004DB350);
    *(u8 **)(m + 0x14) = D_004DB310;
    *(u8 **)(m + 0x24) = D_004DB350;
    w = UiGetWidgetSprite_28fe10(*(s32 *)arg0, 0xA8, 0);
    if (w == 0) {
        return 0;
    }
    UiSetItemIconUv_288e50(w, *(s16 *)(b->m10 + 0x2C), 0x28, 0x2D);
    UiSetItemIconUv_288e50(w + 0x20, *(s16 *)(arg1->m10 + 0x2C), 0x28, 0x2D);
    x = UiGetWidgetTextWidth_28f400(*(s32 *)arg0, 0xA6, 1);
    y = UiGetWidgetTextWidth_28f400(*(s32 *)arg0, 0xA6, 2);
    UiSetSpriteX_28fcd0(*(s32 *)arg0, 0xA5, (x / 2 + y / 2) / 2 + 0x69, 2);
    return 1;
}
