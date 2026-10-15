#include "types.h"

typedef struct {
    u8 pad0[0x10];
    s16 unk10;
    s16 unk12;
} A;

typedef struct {
    u8 pad0[0x11];
    s8 unk11;
} G;

typedef struct {
    u8 pad0[0x18];
    s32 unk18;
} W;

extern W *GetGameData_1fede0();
extern void UiSelFrameSetRect_28db40(void *, s32, s32, s32, s32, s32, s32, s32);
extern s32 UiGetWidgetText_28f620(s32, s32, s32);
extern s32 UiGetWidgetSprite_28fe10(s32, s32, s32);
extern void MenuItemInfoPopupShow_2a33e0(G *, s32, s32, s32, s32 *, s32, s32, s32, f32);
extern void MenuPlaceWidgetAtCurEntry_2a4a10(G *, s32, f32);
extern s32 InvFindByCategoryIndex_3c86e0(s32, s32, s32, s32, s32, s32);
extern void memset(void *, s32, s32);
extern s16 D_004539D0[];
extern s16 D_0047F6D8[] __attribute__((section(".sdata")));
extern s32 D_00482360;
extern G *D_00482374;
extern u8 D_004DB430[];

s32 MenuItemCellFocusCb_346770(A *arg0)
{
    s16 b[5];
    s16 a[9];
    s32 v[4];
    s32 k;
    s16 *s;
    s16 *d;
    s16 *s2;
    s16 *d2;
    s32 r;
    s32 n;

    MenuPlaceWidgetAtCurEntry_2a4a10(D_00482374, 0x227, 24.0f);
    d = a;
    s = D_004539D0;
    n = 9;
    do {
        n--;
        *d = *s;
        s++;
        d++;
    } while (n > 0);
    s2 = D_0047F6D8;
    d2 = b;
    n = 5;
    do {
        n--;
        *d2 = *s2;
        s2++;
        d2++;
    } while (n > 0);
    UiSelFrameSetRect_28db40(D_004DB430, 0x78, a[arg0->unk10], b[arg0->unk12], 0x2A, 0x30, 0x62, 0x49);
    r = InvFindByCategoryIndex_3c86e0(GetGameData_1fede0()->unk18, 0, D_00482374->unk11, arg0->unk10, arg0->unk12, 0);
    k = arg0->unk10 + arg0->unk12 * 8;
    memset(v, 0, 0x10);
    v[0] = UiGetWidgetSprite_28fe10(D_00482360, 0x231, 0);
    v[1] = UiGetWidgetSprite_28fe10(D_00482360, 0x230, 0);
    v[2] = UiGetWidgetText_28f620(D_00482360, 0x230, 0);
    v[3] = UiGetWidgetSprite_28fe10(D_00482360, 0x232, 0);
    MenuItemInfoPopupShow_2a33e0(D_00482374, r, 0x1AA, 0x1A9, v, 0x68, 0x15E, k, 2.0f);
    return 1;
}
