#include "types.h"

typedef struct H38f810 {
    u8  pad00[0x18];
    void *f18;
} H38f810;

typedef struct T38f810 {
    u8  pad00[0x10];
    s16 f10;
    s16 f12;
} T38f810;

extern struct { s32 v; s32 pad[3]; } D_00465A20;
extern void *D_00482374;

extern H38f810 *GetGameData_1fede0(T38f810 *);
extern void *InvFindByCategoryIndex_3c86e0(void *, s32, void *, s32, s32, s32);
extern void *GetMenuWidgetRoot_390d70(s32);
extern void memset(void *, s32, s32);
extern s32 UiGetWidgetSprite_28fe10(void *, s32, s32);
extern s32 UiGetWidgetText_28f620(void *, s32, s32);
extern void MenuItemInfoPopupShow_2a33e0(void *, void *, s32, s32, s32 *, s32, s32, s32, f32);

void *InsectCageMenuItemCellSetupMaybe_38f810(T38f810 *p, void *b)
{
    void *r;
    s32 k;
    void *o;
    s32 buf[4];

    r = InvFindByCategoryIndex_3c86e0(GetGameData_1fede0(p)->f18, 0, b, p->f10, p->f12, 0);
    k = p->f10 + p->f12 * D_00465A20.v;
    o = GetMenuWidgetRoot_390d70(p->f10);
    memset(buf, 0, 0x10);
    buf[0] = UiGetWidgetSprite_28fe10(o, 0x231, 0);
    buf[1] = UiGetWidgetSprite_28fe10(o, 0x230, 0);
    buf[2] = UiGetWidgetText_28f620(o, 0x230, 0);
    buf[3] = UiGetWidgetSprite_28fe10(o, 0x232, 0);
    MenuItemInfoPopupShow_2a33e0(D_00482374, r, 0x1AA, 0x1A9, buf, 0x68, 0x15E, k, 2.0f);
    return r;
}
