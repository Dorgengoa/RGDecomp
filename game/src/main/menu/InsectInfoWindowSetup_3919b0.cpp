#include "types.h"

typedef struct Info {
    u8 pad0[0xC];
    s8 *xC;
    u8 pad10[0x20];
    s8 *x30;
} Info;

class Chr {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 Name(s32 a0) { return VCM(s32, (void *, s32), 0x118, a0); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 V154() { return VCM0(s32, 0x154); }
    s32 V158() { return VCM0(s32, 0x158); }
    
    
    s32 V164() { return VCM0(s32, 0x164); }
    
    
    s32 V170() { return VCM0(s32, 0x170); }
    
    
    s32 V17C() { return VCM0(s32, 0x17C); }
    
    
    s32 Stat(s32 a0) { return VCM(s32, (void *, s32), 0x188, a0); }
    
    
    s32 V194() { return VCM0(s32, 0x194); }
    
    s32 V19C() { return VCM0(s32, 0x19C); }
    s32 V1A0() { return VCM0(s32, 0x1A0); }
    s32 Lv() { return VCM0(s32, 0x1A4); }
    
    s32 V1AC() { return VCM0(s32, 0x1AC); }
    
    s32 V1B4() { return VCM0(s32, 0x1B4); }
    u8 pad4[0xC];
    struct Info *x10;
};

extern "C" {
extern s32 Sprintf_1343b8(s8 *, void *, ...);
extern s32 DrawEnvGetHeight_1451d0(s32);
extern s32 DrawEnvGetWidth_1451e0(s32);
extern s32 GetDrawCtx_15de80(void);
extern s32 UiGetWidgetTextWidth_28f400(s32, s32, s32);
extern void UiSetTextStringCopy_28f4b0(s32, s32, s8 *, s32);
extern void UiSetTextPos_28f5d0(s32, s32, s32, s32, s32);
extern s32 UiFindWidget_290460(s32, s32);
extern void UiSetTextStringPos_290b20(s32, s32, s8 *, s32, s32, s32);
extern void UiSetWidgetPos_290f60(s32, u16, s32, s32);
extern void UiSetWidgetSubItemValue_291250(s32, s32, s32, s64);
extern void UiNineSliceLayoutMaybe_392440(s32 *, s32, s32, s32);
extern void UiIconSetUvByIndexMaybe_3925d0(s32 *, s32, s32, s32, s32);
extern void UiToggleIconPairLayoutRelated_392660(s32 *, s32, s32, s32, s32, s32);
extern void UiGaugeBarLayoutMaybe_392780(s32 *, s32, s32, f32, f32);
extern void UiWindowFrameLayoutMaybe_392bb0(s32 *, s32, s32, s32, s32);
extern void UiSpriteListFillColumnMaybe_3939e0(s32 *, s32, s32, s32, f32, f32);
extern s32 strlen(s8 *);
extern u8 D_00464250[];
extern u8 D_00464258[];
}

extern "C" s32 InsectInfoWindowSetup_3919b0(s32 arg0, Chr *c) {
    s32 wnd;
    s8 buf[0x40] __attribute__((aligned(16)));
    s32 g;
    s32 w;
    s32 h;
    s32 t;
    s32 a;
    s32 b;
    u16 id;
    s32 p;
    f32 f;
    s8 *s;
    s32 len;

    if (arg0 == 0) {
        return 0;
    }
    g = GetDrawCtx_15de80();
    w = DrawEnvGetWidth_1451e0(g);
    h = DrawEnvGetHeight_1451d0(g);
    if (c == 0) {
        return 0;
    }
    UiSetWidgetPos_290f60(arg0, 0xC350, (w - 0x178) / 2, (h - 0x13E) / 2);
    UiWindowFrameLayoutMaybe_392bb0(&wnd, UiFindWidget_290460(arg0, 0xC351), 0x178, 0x13E, 1);
    UiNineSliceLayoutMaybe_392440(&wnd, UiFindWidget_290460(arg0, 0xC352), 0x6E, 0x6E);
    UiSetWidgetPos_290f60(arg0, 0xC352, 0x10, 8);
    UiSetWidgetPos_290f60(arg0, 0xC353, 0x72, 0);
    UiSetTextStringPos_290b20(arg0, 0xC353, (s8 *)c->Name(0), -1, -1, 0);
    UiSetWidgetPos_290f60(arg0, 0xC354, 0, 0x1C);
    UiSetTextStringPos_290b20(arg0, 0xC354, c->x10->xC, -1, -1, 0);
    t = UiGetWidgetTextWidth_28f400(arg0, 0xC354, 0) + 7;
    if (c->Lv() >= 5 && !(c->V1B4() < c->V1AC())) {
        Sprintf_1343b8(buf, D_00464250);
    } else {
        Sprintf_1343b8(buf, D_00464258, c->Lv());
    }
    UiSetTextStringCopy_28f4b0(arg0, 0xC355, buf, 0);
    UiSetWidgetPos_290f60(arg0, 0xC355, t, 0);
    a = UiFindWidget_290460(arg0, 0xC357);
    b = (u8)c->V19C();
    UiToggleIconPairLayoutRelated_392660(&wnd, a, b, (u8)c->V1A0(), 0, 0);
    a = UiFindWidget_290460(arg0, 0xC358);
    UiIconSetUvByIndexMaybe_3925d0(&wnd, a, c->V194(), 0, 0);
    UiSetWidgetPos_290f60(arg0, 0xC357, 0, 0x1F);
    UiSetWidgetPos_290f60(arg0, 0xC358, 0x64, -2);
    if (c->Lv() >= 5 && !(c->V1B4() < c->V1AC())) {
        id = 0xC35B;
        p = UiFindWidget_290460(arg0, id);
        f = (f32)c->V1B4();
        UiGaugeBarLayoutMaybe_392780(&wnd, p, 2, f, (f32)c->V1AC());
    } else {
        id = 0xC35B;
        p = UiFindWidget_290460(arg0, id);
        f = (f32)c->V1B4();
        UiGaugeBarLayoutMaybe_392780(&wnd, p, 1, f, (f32)c->V1AC());
    }
    UiSetWidgetPos_290f60(arg0, 0xC359, 4, 0x1C);
    UiSetWidgetPos_290f60(arg0, id, 0x20, 4);
    p = UiFindWidget_290460(arg0, 0xC35D);
    UiGaugeBarLayoutMaybe_392780(&wnd, p, 0, (f32)c->V164(), 100.0f);
    UiSetWidgetPos_290f60(arg0, 0xC35C, 0x69, -1);
    UiSetWidgetPos_290f60(arg0, 0xC35D, 0x34, 5);
    UiSpriteListFillColumnMaybe_3939e0(&wnd, UiFindWidget_290460(arg0, 0xC35E), 7, 1, 226.0f, 28.0f);
    UiSetWidgetPos_290f60(arg0, 0xC35E, 0, 0x14);
    UiSetWidgetPos_290f60(arg0, 0xC35F, -2, 0x1A);
    UiSetWidgetPos_290f60(arg0, 0xC361, 0, 0x1C);
    UiSetWidgetPos_290f60(arg0, 0xC362, 0, 0x1C);
    UiSetWidgetPos_290f60(arg0, 0xC363, 0x71, 0);
    UiSetWidgetPos_290f60(arg0, 0xC364, 0, 0x1C);
    UiSetWidgetPos_290f60(arg0, 0xC365, 0, 0x1C);
    UiSetWidgetSubItemValue_291250(arg0, 0xC360, 0, c->Stat(0));
    UiSetWidgetSubItemValue_291250(arg0, 0xC363, 0, c->Stat(1));
    UiSetWidgetSubItemValue_291250(arg0, 0xC361, 0, c->Stat(2));
    UiSetWidgetSubItemValue_291250(arg0, 0xC364, 0, c->Stat(3));
    UiSetWidgetSubItemValue_291250(arg0, 0xC362, 0, c->Stat(4));
    UiSetWidgetSubItemValue_291250(arg0, 0xC365, 0, c->Stat(5));
    UiSetWidgetPos_290f60(arg0, 0xC366, 0, 0x76);
    UiSetWidgetPos_290f60(arg0, 0xC36B, 0, 0x1C);
    UiSetWidgetPos_290f60(arg0, 0xC36C, 0, 0x1C);
    UiSetWidgetPos_290f60(arg0, 0xC36A, 0x3C, 0);
    UiSetWidgetSubItemValue_291250(arg0, 0xC36A, 0, c->V158());
    UiSetWidgetSubItemValue_291250(arg0, 0xC36A, 1, c->V154());
    UiSetWidgetSubItemValue_291250(arg0, 0xC36B, 0, c->V170());
    UiSetWidgetSubItemValue_291250(arg0, 0xC36C, 0, c->V17C());
    UiSpriteListFillColumnMaybe_3939e0(&wnd, UiFindWidget_290460(arg0, 0xC371), 3, 1, 102.0f, 28.0f);
    UiSetWidgetPos_290f60(arg0, 0xC371, 4, 0xE);
    UiSetWidgetPos_290f60(arg0, 0xC369, 0x6A, 0);
    UiNineSliceLayoutMaybe_392440(&wnd, UiFindWidget_290460(arg0, 0xC36E), 0x158, 0x68);
    s = c->x10->xC;
    UiSetWidgetPos_290f60(arg0, 0xC36E, 0, 0x50);
    UiSetTextStringPos_290b20(arg0, 0xC36E, s, -1, -1, 0);
    len = strlen(s);
    UiSetTextPos_28f5d0(arg0, 0xC36E, 6, 6, 0);
    UiSetTextPos_28f5d0(arg0, 0xC36E, len * 8 + 6, 6, 1);
    UiSetTextStringPos_290b20(arg0, 0xC36F, c->x10->x30, -1, -1, 0);
    UiSpriteListFillColumnMaybe_3939e0(&wnd, UiFindWidget_290460(arg0, 0xC370), 1, 1, 328.0f, 0.0f);
    UiSetWidgetPos_290f60(arg0, 0xC370, 6, 0x18);
    return 1;
}
