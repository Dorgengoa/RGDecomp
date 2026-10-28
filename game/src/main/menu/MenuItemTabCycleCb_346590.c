/* rgp:protos */
#define RGP_SELF_MenuItemTabCycleCb_346590 1
#include "port/game_protos.h"
#line 1
/* PARKED s15i: ~14 unknown-typed ("?") externs, several taking 5+ params
 * with unresolved types, plus a byte-field flag manipulation on
 * D_00482374->unk11 shared with MenuItemSelectLastTab_2b30d0/MenuInvGridReturnState_2abbc0 in this lane
 * (already-drafted siblings that could help pin the struct if revisited);
 * 0 round trips spent. Not attempted -- lower priority than units with
 * fewer unresolved externs. */
/* s49m: MATCH */
#include "types.h"

typedef struct Menu {
    u8 pad0[0x10];
    s16 x;
    s16 y;
} Menu;

extern u8 D_004B2570[];
extern u8 *D_00482374;
extern s32 D_00482360;
extern s32 D_00482E34;
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern void *memset(void *, s32, s32);
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 MenuItemTabCycleCb_346590(Menu *o)
{
    s32 buf[4] __attribute__((aligned(16)));
    s32 k;
    u8 *p;
    u8 *pad;
    s32 cur;
    s32 r;
    s32 max;
    s32 changed;

    pad = D_004B2570;
    cur = (s8)D_00482374[0x11];
    max = (s8)D_00482374[0x10] - 1;
    changed = 0;
    if (PadIsTriggered_1839f0(pad, 4) != 0) {
        cur--;
        if (cur < 0) {
            cur = max - 1;
        }
        changed = 1;
    } else if (PadIsTriggered_1839f0(pad, 8) != 0) {
        cur++;
        if (cur >= max) {
            cur = 0;
        }
        changed = 1;
    }
    if (changed != 0) {
    D_00482374[0x11] = cur;
    MenuDrawItemTabs_2a4ee0(D_00482374, 0x67, 0);
    MenuFillItemGrid_2a4b40(D_00482374, 0x76);
    MenuFillItemCounts_2a3d90(D_00482374, 0x77);
    p = ((u8 *)GetGameData_1fede0());
    if (p == NULL) {
        return 0;
    }
    r = ((s32)InvFindByCategoryIndex_3c86e0(*(s32 *)(p + 0x18), 0, cur, o->x, o->y, 0));
    k = o->x + o->y * 8;
    memset(buf, 0, 0x10);
    buf[0] = ((s32)UiGetWidgetSprite_28fe10(D_00482360, 0x231, 0));
    buf[1] = ((s32)UiGetWidgetSprite_28fe10(D_00482360, 0x230, 0));
    buf[2] = ((s32)UiGetWidgetText_28f620(D_00482360, 0x230, 0));
    buf[3] = ((s32)UiGetWidgetSprite_28fe10(D_00482360, 0x232, 0));
    MenuItemInfoPopupShow_2a33e0(D_00482374, r, 0x1AA, 0x1A9, buf, 0x68, 0x15E, k, 2.0f);
    SoundPlayScaledVolume_1b9520(D_00482E34, 0xB, 0, 1.0f);
    }
    return 1;
}
