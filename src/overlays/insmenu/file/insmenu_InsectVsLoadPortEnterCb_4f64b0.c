#include "types.h"

/* insmenu 0x004F64B0 (164 bytes, 41 instructions, 8 calls) -- close the detail
 * pane and reset every selector to -1.  The `sb $0` sits in the first call's
 * delay slot because the store is written BEFORE the call.
 */

typedef struct Pane Pane;
struct Pane {
    u8 pad00[0x12];
    s16 field012;
};

extern u8 D_00484388;       /* gp - 0xDE8 */

extern void func_37B460(s32 a);
extern void insmenu_InsectVsLoadSlotCursorBob_4f6810(Pane *o, void *w, s32 c);
extern void insmenu_InsectVsSavePortSelectDraw_4f6bf0(s32 a);
extern void func_37B800(s32 a);
extern void insmenu_InsectVsSaveHighlightOption_4f6bb0(s32 a);
extern void insmenu_InsectVsSaveShowMsg_4f6e00(s32 a, s32 b, s32 c);
extern void insmenu_InsectVsLoadPortCursorBob_4f68d0(s32 a, s32 b, s32 c);
extern void func_376B10(s32 a);
extern void func_377830(s32 a, s32 b, s32 c, s32 d, s32 e);

s32 insmenu_InsectVsLoadPortEnterCb_4f64b0(Pane *o, void *w)
{
    D_00484388 = 0;
    func_37B460(0x890D);
    insmenu_InsectVsLoadSlotCursorBob_4f6810(o, w, 0);
    insmenu_InsectVsSavePortSelectDraw_4f6bf0(-1);
    func_37B800(-1);
    insmenu_InsectVsSaveHighlightOption_4f6bb0(-1);
    insmenu_InsectVsSaveShowMsg_4f6e00(0x18, 0, -1);
    insmenu_InsectVsLoadPortCursorBob_4f68d0(o->field012, 1, 1);
    func_376B10(0);
    func_377830(0x890C, 0x15B, 3, 0x32, 0);
    return 1;
}
