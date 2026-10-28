/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsSourceChoiceStep_4f8710 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* insmenu 0x004F8710 (240 bytes) -- run the yes/no prompt one frame: latch the
 * answer into the mode when the widget settles, then hand it on.
 *
 * ★ Both the r == 1 and the r == 2 arms raise the SAME event, and each has its
 * own call: the shared join is only the epilogue, so this is an if/else-if with
 * duplicated bodies rather than an `||`. */

typedef struct Widget Widget;
struct Widget {
    u8  pad00[0x16];
    s16 field16;
};

extern u8 insmenu_D_004FA180[];
extern u8 insmenu_D_004FA1A0[];
extern u8 D_004B2570;
extern u8 D_004B27E0;
extern u8 D_004842E8;           /* gp - 0xE88, passed by address */
extern s16 D_0048436C;          /* gp - 0xE04 */
extern f32 D_0047D488;          /* gp - 0x7CE8 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 insmenu_InsectVsSourceChoiceStep_4f8710(s32 a, s32 start)
{
    Widget *w;
    s32 r;
    s16 sel;

    if (start) {
        UiEntryListSelectByTag_28ea90(insmenu_D_004FA1A0, 0x88C2, 0);
        UiFadeWidgetAlpha_290690(insmenu_D_004FA180, 0x5E, 1.0f, D_0047D488, -1.0f);
    }
    r = MenuGridCursorInputPad2_28e100(insmenu_D_004FA1A0, &D_004B2570, &D_004B27E0, 0);
    if (r == 1) {
        w = ((Widget *)UiEntryListFindByTag_28ea40(insmenu_D_004FA1A0, 0x88C2));
        if (w != 0) {
            sel = w->field16;
            if (sel == 0) {
                D_0048436C = 1;
            } else if (sel == 1) {
                D_0048436C = 2;
            }
        }
        StateMachineSetState_28ede0(&D_004842E8, 0x88C8, 0);
    } else if (r == 2) {
        StateMachineSetState_28ede0(&D_004842E8, 0x88C8, 0);
    }
    return 1;
}
