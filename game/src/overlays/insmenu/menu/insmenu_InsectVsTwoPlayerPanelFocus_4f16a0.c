/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsTwoPlayerPanelFocus_4f16a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* insmenu 0x004F16A0 -- the insmenu_FUN_004F0A00 family: build the panel, count how
 * many of the item's flag bits are set, map the resulting id through a table
 * into a widget index and lay the panel out.  The recipes (bitfields for the
 * one-bit tests, switch-not-chain for the dispatch, forwarded `p->field12`)
 * were all measured on 004F0A00 and 004F00D0; only what differs is noted here.
 *
 * Three flag bits (0, 1 and 2) and a four-case dispatch.  Two extra calls run
 * BETWEEN the counting block and the insmenu_FUN_004EA0D0 guard, so they sit
 * outside both.  The store is OUTSIDE the `h != 0` guard -- retail sinks it
 * into `beqz $16`'s delay slot and then RELOADS `lw $3, 0x0($16)`, which is
 * the 004F0A00 spelling.  The multiplier is the literal 57 (sll/subu/sll/addu),
 * not p->field06. */

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
extern s32 insmenu_D_004F9980[];

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

void insmenu_InsectVsTwoPlayerPanelFocus_4f16a0(void)
{
    Panel *p;
    Item *h;
    s32 n;
    s32 k;

    UiEntryListSelectByTag_28ea90(insmenu_D_004FA1A0, 0x7535, 0);
    p = ((Panel *)UiEntryListGetCurrentData_28ec60(insmenu_D_004FA1A0));
    p->field06 = 0x39;
    p->field0A = 3;
    h = ((Item *)RecordGetPayloadIfKind1E_430b70(((Handle *)GetGameData_1fede0())->field24));
    n = 0;
    if (h != 0) {
        if (h->bit0) {
            n++;
        }
        if (h->bit1) {
            n++;
        }
        if (h->bit2) {
            n++;
        }
        p->field0A = n;
    }
    insmenu_InsectVsTwoPlayerPanelBright_4f19d0();
    insmenu_InsectVsListSetRowColors_4ea110(0x1B, 3, n);
    if (insmenu_InsectVsTakeCancelFlag_4ea0d0() == 0) {
        k = 0;
        h->field00 = insmenu_D_004F9980[n];
        if (h != 0) {
            switch (h->field00) {
            case 0x12E:
                k = 0;
                break;
            case 0x12F:
                k = 1;
                break;
            case 0x130:
                k = 2;
                break;
            case 0x131:
                k = 3;
                break;
            }
        }
        p->field12 = k;
        UiSetWidgetPos_290f60(insmenu_D_004FA180, 0x14, p->field00, p->field02 + p->field12 * 57);
        UiSetWidgetPos_290f60(insmenu_D_004FA180, 0x13, 0, p->field12 * 57);
        UiSetWidgetAlpha_2907a0(insmenu_D_004FA180, 0x13, 1.0f);
    }
    insmenu_InsectVsTwoPlayerCursorFadeIn_4f1980();
}
