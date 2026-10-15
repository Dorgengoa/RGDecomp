#include "types.h"

/* insmenu 0x004F4FD0 (128 bytes, 32 instructions, 6 calls) -- open one detail
 * pane.  The two halfword stores go through the SAME base, so their emission
 * order IS the source order -- 0xE then 0xA, not ascending.
 */

typedef struct Pane Pane;
struct Pane {
    u8 pad00[0xA];
    s16 field00A;
    u8 pad00C[0x2];
    s16 field00E;
    u8 pad010[0x2];
    s16 field012;
    u8 pad014[0x2];
    s16 field016;
};

extern void func_37B490(s32 a);
extern void insmenu_InsectVsLoadSlotCursorBob_4f6810(Pane *o, void *w, s32 c);
extern void insmenu_InsectVsSaveHighlightOption_4f6bb0(s32 a);
extern void func_3777A0(Pane *o, s32 b, s32 c);
extern void func_37A2B0(s32 a);
extern void insmenu_InsectVsTeamListTitleUpdate_4f5400(void);

s32 insmenu_InsectVsTeamListEnterCb_4f4fd0(Pane *o, void *w)
{
    o->field00E = 0x13;
    o->field00A = 2;
    func_37B490(0x890D);
    insmenu_InsectVsLoadSlotCursorBob_4f6810(o, w, 1);
    insmenu_InsectVsSaveHighlightOption_4f6bb0(o->field012);
    func_3777A0(o, 0x890C, 0);
    func_37A2B0(o->field016);
    insmenu_InsectVsTeamListTitleUpdate_4f5400();
    return 1;
}
