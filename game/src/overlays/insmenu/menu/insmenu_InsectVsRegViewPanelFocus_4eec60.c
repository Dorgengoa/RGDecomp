/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsRegViewPanelFocus_4eec60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* insmenu 0x004EEC60 -- the insmenu_FUN_004F0A00 family: build the panel, count how
 * many of the item's flag bits are set, map the resulting id through a table
 * into a widget index and lay the panel out.  The recipes (bitfields for the
 * one-bit tests, switch-not-chain for the dispatch, forwarded `p->field12`)
 * were all measured on 004F0A00 and 004F00D0; only what differs is noted here.
 *
 * One flag bit only (bit 0), and the fourth argument is `p->field12 *
 * p->field06` -- a real `mult` against the field stored as 0x39 above, not the
 * shift chain 004F0A00 uses for a literal 57.
 * The store lands in the FIRST CASE COMPARE's delay slot, so it is written
 * INSIDE the `h != 0` guard (the 004F00D0 spelling, not 004F0A00's). */

typedef struct {
    s16 field00;
    s16 field02;
    u8 pad04[2];
    s16 field06;
    u8 pad08[2];
    s16 field0A;
    u8 pad0C[6];
    s16 field12;
} Panel;

typedef struct {
    s32 field00;
    u8 bit0 : 1;
    u8 bit1 : 1;
    u8 bit2 : 1;
} Item;

typedef struct {
    u8 pad00[0x24];
    void *field24;
} Handle;

/* Overlay data, outside the gp window 0x47D170..0x48D170 -- must be `const`. */
extern u8 insmenu_D_004FA1A0[];
extern u8 insmenu_D_004FA180[];
extern s32 insmenu_D_004F99D8[];

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void insmenu_InsectVsRegViewPanelFocus_4eec60(void)
{
    Panel *p;
    Item *h;
    s32 n;
    s32 k;

    UiEntryListSelectByTag_28ea90(insmenu_D_004FA1A0, 0x7535, 0);
    p = ((Panel *)UiEntryListGetCurrentData_28ec60(insmenu_D_004FA1A0));
    p->field06 = 0x39;
    p->field0A = 1;
    h = ((Item *)RecordGetPayloadIfKind3E_430ad0(((Handle *)GetGameData_1fede0())->field24));
    n = 0;
    if (h != 0) {
        if (h->bit0) {
            n++;
        }
        p->field0A = n;
    }
    if (insmenu_InsectVsTakeCancelFlag_4ea0d0() == 0) {
        k = 0;
        if (h != 0) {
            h->field00 = insmenu_D_004F99D8[n];
            switch (h->field00) {
            case 0x26E:
                k = 0;
                break;
            case 0x26F:
                k = 1;
                break;
            }
        }
        p->field12 = k;
        UiSetWidgetPos_290f60(insmenu_D_004FA180, 0x58, p->field00, p->field02 + p->field12 * p->field06);
        UiSetWidgetPos_290f60(insmenu_D_004FA180, 0x54, 0, p->field12 * p->field06);
        UiSetWidgetAlpha_2907a0(insmenu_D_004FA180, 0x54, 1.0f);
    }
    insmenu_InsectVsRegTeamPanelBright_4eef10();
    insmenu_InsectVsListSetRowColors_4ea110(0x55, 2, n);
    insmenu_InsectVsRegTeamCursorFadeIn_4eeec0();
}
