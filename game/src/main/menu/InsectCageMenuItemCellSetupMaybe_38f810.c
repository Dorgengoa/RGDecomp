/* rgp:protos */
#define RGP_SELF_InsectCageMenuItemCellSetupMaybe_38f810 1
#include "port/game_protos.h"
#line 1
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

/*rgp*/
/*rgp*/
/*rgp*/
extern void memset(void *, s32, s32);
/*rgp*/
/*rgp*/
/*rgp*/

void *InsectCageMenuItemCellSetupMaybe_38f810(T38f810 *p, void *b)
{
    void *r;
    s32 k;
    void *o;
    s32 buf[4] __attribute__((aligned(16)));

    r = InvFindByCategoryIndex_3c86e0(((H38f810 *)GetGameData_1fede0())->f18, 0, b, p->f10, p->f12, 0);
    k = p->f10 + p->f12 * D_00465A20.v;
    o = GetMenuWidgetRoot_390d70();
    memset(buf, 0, 0x10);
    buf[0] = ((s32)UiGetWidgetSprite_28fe10(o, 0x231, 0));
    buf[1] = ((s32)UiGetWidgetSprite_28fe10(o, 0x230, 0));
    buf[2] = ((s32)UiGetWidgetText_28f620(o, 0x230, 0));
    buf[3] = ((s32)UiGetWidgetSprite_28fe10(o, 0x232, 0));
    MenuItemInfoPopupShow_2a33e0(D_00482374, r, 0x1AA, 0x1A9, buf, 0x68, 0x15E, k, 2.0f);
    return r;
}
