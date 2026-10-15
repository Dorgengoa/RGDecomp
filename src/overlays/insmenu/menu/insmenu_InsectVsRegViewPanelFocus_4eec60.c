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
extern const u8 D_004FA1A0[];
extern const u8 D_004FA180[];
extern const s32 D_004F99D8[];

extern void func_28EA90(const void *a, s32 b, s32 c);
extern Panel *func_28EC60(const void *a);
extern Handle *func_1FEDE0(void);
extern Item *func_430AD0(void *a);
extern u8 insmenu_InsectVsTakeCancelFlag_4ea0d0(void);
extern void func_290F60(const void *a, s32 b, s32 c, s32 d);
extern void func_2907A0(const void *a, s32 b, f32 t);
extern void insmenu_InsectVsListSetRowColors_4ea110(s32 a, s32 b, s32 c);
extern void insmenu_InsectVsRegTeamPanelBright_4eef10(void);
extern void insmenu_InsectVsRegTeamCursorFadeIn_4eeec0(void);

void insmenu_InsectVsRegViewPanelFocus_4eec60(void)
{
    Panel *p;
    Item *h;
    s32 n;
    s32 k;

    func_28EA90(D_004FA1A0, 0x7535, 0);
    p = func_28EC60(D_004FA1A0);
    p->field06 = 0x39;
    p->field0A = 1;
    h = func_430AD0(func_1FEDE0()->field24);
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
            h->field00 = D_004F99D8[n];
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
        func_290F60(D_004FA180, 0x58, p->field00, p->field02 + p->field12 * p->field06);
        func_290F60(D_004FA180, 0x54, 0, p->field12 * p->field06);
        func_2907A0(D_004FA180, 0x54, 1.0f);
    }
    insmenu_InsectVsRegTeamPanelBright_4eef10();
    insmenu_InsectVsListSetRowColors_4ea110(0x55, 2, n);
    insmenu_InsectVsRegTeamCursorFadeIn_4eeec0();
}
