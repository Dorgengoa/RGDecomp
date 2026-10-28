/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsTeamInfoStepCb_4f43f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* insmenu 0x004F43F0 (484 bytes, 121 instructions, 21 calls) -- the map's
 * cancel path.  Both arms of the outer chain are the same four-term
 * short-circuit against a different mask, and the `func_2F6660` guard is a
 * single condition rather than an early return so the shared epilogue keeps
 * its predecessors and the branch into it stays LIKELY.
 */

typedef struct Ctx Ctx;

typedef struct Handle Handle;
struct Handle {
    u8  pad00[0x24];
    Ctx *field24;
};

typedef struct Obj Obj;
struct Obj {
    u8  pad00[0xE6];
    s16 fieldE6;
};

extern u8 insmenu_D_004FA180[];
extern u8 insmenu_D_004FA1A0[];
extern u8 D_004B2570[];
extern u8 D_004B27E0[];

extern u8   D_00484360;     /* gp - 0xE10 */
extern Obj *D_00484104;     /* gp - 0x106C */

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
/*rgp*/
/*rgp*/

s32 insmenu_InsectVsTeamInfoStepCb_4f43f0(void)
{
    char buf[0x100] __attribute__((aligned(16)));
    char *p;
    u32 n;
    s32 tag;

    if (GetPauseStep_2f6660() == 0) {
        if ((PadIsTriggered_1839f0(D_004B2570, 0x20) != 0) ||
            ((((unsigned char)IsPad2Enabled_2882c0()) != 0) && (PadIsTriggered_1839f0(D_004B27E0, 0x20) != 0))) {
            UiSetWidgetsVisibleById_291110(insmenu_D_004FA180, 0x9CA7, 0, 1);
            UiSetWidgetsVisibleById_291110(insmenu_D_004FA180, 0x9CAA, 1, 1);
            UiSetWidgetsVisibleById_291110(insmenu_D_004FA180, 0x88CC, 1, 1);
            UiSetWidgetsVisibleById_291110(insmenu_D_004FA180, 0x88E0, 1, 1);
            UiSetWidgetsVisibleById_291110(insmenu_D_004FA180, 0x88F4, 1, 1);
            SaveUiWidgetFadeIn_37b490(0x890D);
            UiEntryListSelectByTag_28ea90(insmenu_D_004FA1A0, 0x88BD, 0);
        } else if ((PadIsTriggered_1839f0(D_004B2570, 0x10) != 0) ||
                   ((((unsigned char)IsPad2Enabled_2882c0()) != 0) && (PadIsTriggered_1839f0(D_004B27E0, 0x10) != 0))) {
            D_00484360 = 1;
            if (D_00484104 != 0) {
                TextEntrySetMode_436450(D_00484104, (long long)(4));
                TextEntrySetState_434410(D_00484104, 0x6D61, 1);
                D_00484104->fieldE6 = 0;
                tag = ((s32)insmenu_InsectVsTeamListGetSelRec_4f93b0());
                p = buf;
                n = 0x100;
                if (p != 0) {
                    do {
                        *p = 0;
                        n -= 1;
                        p += 1;
                    } while (n != 0);
                }
                InsectTeamCodeEncode_4319f0(((Handle *)GetGameData_1fede0())->field24, buf, tag);
                TextEntryBuildTemplateText_4356d0(D_00484104, 0, buf);
                UiEntryListSelectByTag_28ea90(insmenu_D_004FA1A0, 0x88C1, 0);
            }
        }
    }
    return 1;
}
