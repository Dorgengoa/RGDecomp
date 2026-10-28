/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsTeamViewState_4f8a00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* insmenu 0x004F8A00 (940 bytes, 235 instructions, 33 calls) -- the map-marker
 * toggle.  ⚠ TWO parameters: the flag it tests arrives in $5, so it is the
 * SECOND one, and the first is never read.  m2c reads the `daddu $16, $5, $0`
 * as `arg1`.
 */

typedef struct Kind Kind;
struct Kind {
    u8  pad00[8];
    s16 field08;
};

typedef struct Ctx Ctx;
struct Ctx {
    u8   pad0000[0x1188];
    Kind *field1188;
};

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

extern u8   D_004842E8;     /* gp - 0xE88, passed by address */
extern s16  D_00484364;     /* gp - 0xE0C */
extern volatile s16 D_00484368;     /* gp - 0xE08 */
extern u8   D_00484360;     /* gp - 0xE10 */
extern u8   D_00484358;     /* gp - 0xE18 */
extern Obj *D_00484104;     /* gp - 0x106C */
extern f32  D_0047D3C8;     /* gp - 0x7DA8 */

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
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 insmenu_InsectVsTeamViewState_4f8a00(s32 p1, s32 show)
{
    Handle *hnd;
    Handle *cur;
    s32 mode;
    s16 kind;
    u8  ok;
    s32 arg;
    s32 tag;
    s32 arg2;
    s32 tag2;
    char buf[0x100] __attribute__((aligned(16)));
    char *p;
    u32 n;

    hnd = ((Handle *)GetGameData_1fede0());
    if (show != 0) {
        UiEntryListSelectByTag_28ea90(insmenu_D_004FA1A0, 0x7534, 0);
    }
    mode = MenuGridCursorInputPad2_28e100(insmenu_D_004FA1A0, D_004B2570, D_004B27E0, 0);
    if ((u32)(mode - 1) < 2) {
        cur = ((Handle *)GetGameData_1fede0());
        kind = cur->field24->field1188->field08;
        ok = 0;
        if ((kind == 0x1F6) || (kind == 0x1F7) || (kind == 0x193)) {
            ok = 1;
        }
        if ((mode == 1) && ok && (D_00484358 == 0)) {
            D_00484368 = 0;
            D_00484360 = 0;
            InsectVsTeamInfoLayoutMaybe_379400(RecordGetNameSlot_430580(cur->field24, 0), 2);
            D_00484364 = 0;
            StateMachineSetState_28ede0(&D_004842E8, 0x88CC, 0);
        } else if ((mode == 2) && ok && (D_00484358 == 0)) {
            D_00484368 = 0;
            D_00484360 = 0;
            InsectVsTeamInfoLayoutMaybe_379400(RecordGetNameSlot_430580(cur->field24, 0), 2);
            D_00484364 = 1;
            StateMachineSetState_28ede0(&D_004842E8, 0x88CC, 0);
        } else if (D_00484358 != 0) {
            if (mode == 2) {
                D_00484358 = 0;
            }
            if (D_00484360 != 0) {
                InsectVsTeamInfoLayoutMaybe_379400(RecordGetNameSlot_430580(cur->field24, 0), 2);
                D_00484360 = 0;
            }
            UiFadeWidgetAlpha_290690(insmenu_D_004FA180, 0x9CA7, 0.0f, D_0047D3C8, -1.0f);
            StateMachineSetState_28ede0(&D_004842E8, 0x88C5, 0);
        } else {
            UiFadeWidgetAlpha_290690(insmenu_D_004FA180, 0x9CA7, 0.0f, D_0047D3C8, -1.0f);
            if (D_00484360 != 0) {
                InsectVsTeamInfoLayoutMaybe_379400(RecordGetNameSlot_430580(cur->field24, 0), 0);
            }
            D_00484360 = 0;
            StateMachineSetState_28ede0(&D_004842E8, 0x88C5, 0);
        }
    }
    if ((GetPauseStep_2f6660() == 0) &&
        ((PadIsTriggered_1839f0(D_004B2570, 0x10) != 0) ||
         ((((unsigned char)IsPad2Enabled_2882c0()) != 0) && (PadIsTriggered_1839f0(D_004B27E0, 0x10) != 0)))) {
        if (D_00484368 == 0) {
            D_00484368 = 1;
        } else {
            D_00484368 = 0;
        }
        if (D_00484368 == 0) {
            D_00484360 = 0;
            tag = RecordGetNameSlot_430580(hnd->field24, 0);
            arg = 0;
            if (((unsigned char)insmenu_InsectVsBattleTeamPending_4f9680()) != 0) {
                arg = 2;
            }
            InsectVsTeamInfoLayoutMaybe_379400(tag, arg);
        } else {
            D_00484360 = 1;
            if (D_00484104 != 0) {
                TextEntrySetMode_436450(D_00484104, (long long)(4));
                TextEntrySetState_434410(D_00484104, 0x6D61, 1);
                D_00484104->fieldE6 = 0;
                tag2 = RecordGetNameSlot_430580(hnd->field24, 0);
                p = buf;
                n = 0x100;
                if (p != 0) {
                    do {
                        *p = 0;
                        n -= 1;
                        p += 1;
                    } while (n != 0);
                }
                InsectTeamCodeEncode_4319f0(((Handle *)GetGameData_1fede0())->field24, buf, tag2);
                TextEntryBuildTemplateText_4356d0(D_00484104, 0, buf);
                arg2 = 0;
                if (((unsigned char)insmenu_InsectVsBattleTeamPending_4f9680()) != 0) {
                    arg2 = 2;
                }
                InsectVsTeamPanelSetupMaybe_379000(tag2, arg2);
            }
        }
    }
    return 1;
}
