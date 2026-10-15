#include "types.h"

/* insmenu 0x004F45E0 (204 bytes, 51 instructions, 9 calls) -- enter the detail
 * pane: hide the four list widgets, drop the page, show the pane widget and
 * hand the opened record to the pane driver.  Every id is `ori` because none
 * of them fits a signed 16-bit immediate.
 */

extern const u8 D_004FA180[];

extern void *insmenu_InsectVsTeamListGetSelRec_4f93b0(void);
extern void func_291110(const void *a, s32 b, s32 c, s32 d);
extern void func_37B460(s32 a);
extern void func_2907A0(const void *a, s32 b, f32 t);
extern void func_379400(void *a, s32 b);

s32 insmenu_InsectVsTeamInfoEnterCb_4f45e0(void)
{
    void *r;

    r = insmenu_InsectVsTeamListGetSelRec_4f93b0();
    func_291110(D_004FA180, 0x9CAA, 0, 1);
    func_291110(D_004FA180, 0x88CC, 0, 1);
    func_291110(D_004FA180, 0x88E0, 0, 1);
    func_291110(D_004FA180, 0x88F4, 0, 1);
    func_37B460(0x890D);
    func_291110(D_004FA180, 0x9CA7, 1, 1);
    func_2907A0(D_004FA180, 0x9CA7, 1.0f);
    func_379400(r, 1);
    return 1;
}
