#include "types.h"

typedef struct R298600 {
    s32 m00;
    s32 m04;
    u8 pad08[2];
    u16 lo : 2;
    u16 f : 14;
} R298600;

extern u8 D_004DB190[];
extern struct { s32 v; s32 pad[3]; } D_004DB198;
extern void *D_00482334;
extern s16 D_0048239C;
extern f32 D_0047DD80;
extern f32 D_0047DD88;

extern void *GetMenuResGroup_206a40(void);
extern R298600 *ResGroupListFindById_42c500(void *o, s32 id);
extern void UiWidgetListReset_2912e0(void *w);
extern void UiInitWidgetPool_290390(void *w, void *a, s32 b);
extern void UiAddWidgets_2901d0(void *w, s32 a, s32 b, s32 c);
extern void UiTextStyleReset_290450(void *w);
extern void UiSetWidgetsVisibleById_291110(void *w, s32 id, s32 a, s32 b);
extern void UiSetWidgetAlpha_2907a0(void *w, s32 id, f32 t);
extern void UiSetWidgetPos_290f60(void *w, s32 id, s32 x, s32 y);
extern void UiSetWidgetColor_2905b0(void *w, s32 id, f32 a, f32 b, f32 c, f32 d);
extern void UiFadeWidgetAlpha_290690(void *w, s32 id, f32 a, f32 b, f32 c);

void MenuOpeningPanelSetupMaybe_298600(void)
{
    R298600 *r;
    s32 a;
    s32 b;

    r = ResGroupListFindById_42c500(GetMenuResGroup_206a40(), 0x2F);
    a = r->m04;
    b = r->f;
    UiWidgetListReset_2912e0(D_004DB190);
    UiInitWidgetPool_290390(D_004DB190, D_00482334, b);
    UiAddWidgets_2901d0(D_004DB190, a, 0, 0);
    D_004DB198.v = 0x32B;
    UiTextStyleReset_290450(D_004DB190);
    UiSetWidgetsVisibleById_291110(D_004DB190, 4, 1, 1);
    UiSetWidgetsVisibleById_291110(D_004DB190, 1, 1, 1);
    UiSetWidgetsVisibleById_291110(D_004DB190, 3, 1, 1);
    UiSetWidgetAlpha_2907a0(D_004DB190, 7, 1.0f);
    UiSetWidgetAlpha_2907a0(D_004DB190, 6, 1.0f);
    UiSetWidgetPos_290f60(D_004DB190, 2, 0xFA, 0xA2);
    UiSetWidgetPos_290f60(D_004DB190, 1, -0x40, -0x40);
    UiSetWidgetPos_290f60(D_004DB190, 7, 0xE7, 0x89);
    UiSetWidgetPos_290f60(D_004DB190, 6, 0xF6, 0x9A);
    UiSetWidgetPos_290f60(D_004DB190, 5, 0xED, 0x8E);
    UiSetWidgetColor_2905b0(D_004DB190, 5, 0.0f, 0.0f, 0.0f, D_0047DD80);
    if (D_0048239C == 1) {
        UiSetWidgetAlpha_2907a0(D_004DB190, 1, 1.0f);
    } else {
        UiFadeWidgetAlpha_290690(D_004DB190, 1, 1.0f, D_0047DD88, 0.0f);
        UiFadeWidgetAlpha_290690(D_004DB190, 2, 1.0f, D_0047DD88, 0.0f);
    }
}
