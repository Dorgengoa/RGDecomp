/* rgp:protos */
#define RGP_SELF_normal_TransHunterRankListState_51dd40 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x0051DD40 -- the 0x7642/0x7644 list pad handler.  FRESH unit,
 * session 31 lane a1.  Structural twin of normal_TransHunterBountyListState_51f630 (same
 * func_28E170 / func_28EC60 / four-D_004B2570-test shape, same Rec layout,
 * same (s16)(rec->f0A + 1) narrowed page stride), but:
 *   - takes no parameters (frame -0x30, sq $16 / sq $17 / sd $31 only),
 *   - the confirm arm (code == 1) is a func_290690 fade plus a
 *     func_3CCAC0 count clamped to 1..100 and stored decremented into
 *     D_00480784, then a normal_TransHunterRewardFindNext_51d320 poll,
 *   - every path falls through a shared tail `D_004848B4 = rec->f12;`.
 */

typedef struct Rec {
    u8  pad00[2];
    s16 f02;
    u8  pad04[2];
    s16 f06;
    u8  pad08[2];
    s16 f0A;
    u8  pad0C[2];
    s16 f0E;
    u8  pad10[2];
    s16 f12;
    u8  pad14[2];
    s16 f16;
} Rec;

typedef struct Pad { u8 pad00[0x14]; s32 f14; } Pad;
typedef struct Ent { u8 pad00[0x10]; void *f10; } Ent;

extern u8 D_004B2570[];

extern f32   D_0047D998;          /* gp - 0x77D8 */
extern f32   D_0047D9B8;          /* gp - 0x77B8 */
extern s16   D_00480784;          /* gp - 0x49EC */
extern void *D_0048470C;          /* gp - 0xA64  */
extern void *D_00484710;          /* gp - 0xA60  */
extern Pad  *D_00484720;          /* gp - 0xA50  */
extern s16   D_004848B4;          /* gp - 0x8BC  */
extern f32   D_004848B8;          /* gp - 0x8B8  */
extern s16   D_004848F0;          /* gp - 0x880  */

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

s32 normal_TransHunterRankListState_51dd40(void)
{
    s32  code;
    Rec *rec;
    s32  n;

    code = MenuGridCursorInput_28e170(D_00484720, D_004B2570, 0, 0);
    rec = ((Rec *)UiEntryListGetCurrentData_28ec60(D_00484720));
    if (code == 1) {
        UiFadeWidgetAlpha_290690(D_00484710, 0x764B, 0.0f, D_0047D9B8, -1.0f);
        n = ((short)StateVarGet_3ccac0(((Ent *)GetGameData_1fede0())->f10, 0xF));
        if (n <= 0 || n > 0x64) {
            n = 0x64;
        }
        D_00480784 = n - 1;
        if (normal_TransHunterRewardFindNext_51d320() > 0) {
            D_004848F0 = 0;
            StateMachineSetState_28ede0(D_0048470C, 0x1C, 0);
        } else {
            StateMachineSetState_28ede0(D_0048470C, 0x1B, 0);
        }
    } else if (PadIsTriggered_1839f0(D_004B2570, 0x8000) != 0) {
        if (rec->f12 > 0 || rec->f16 > 0) {
            MenuGridCursorRequestSe_28e9e0(D_00484720, 0);
        }
        if (rec->f16 > 0) {
            rec->f16 = rec->f16 - (s16)(rec->f0A + 1);
            if (rec->f16 < 0) {
                rec->f16 = 0;
                rec->f12 = 0;
                UiSetSpritePos_28fd10(D_00484710, 0x7642, 0x1E, rec->f02, 0);
            }
            normal_TransHunterRankListFill_51d820(rec->f16);
        } else {
            rec->f16 = 0;
            rec->f12 = 0;
            UiSetSpritePos_28fd10(D_00484710, 0x7642, 0x1E, rec->f02, 0);
        }
        if (rec->f16 < 0) {
            rec->f16 = 0;
        }
        UiMoveWidgetUniform_290f50(D_00484710, 0x7644, 0, (s32)((f32)rec->f16 * D_004848B8), D_0047D998, 0
);
    } else if (PadIsTriggered_1839f0(D_004B2570, 0x2000) != 0) {
        if (rec->f12 < rec->f0A || rec->f16 < rec->f0E - rec->f0A) {
            MenuGridCursorRequestSe_28e9e0(D_00484720, 0);
        }
        if (rec->f16 < rec->f0E - rec->f0A) {
            rec->f16 = rec->f16 + (s16)(rec->f0A + 1);
            if (rec->f16 > rec->f0E - rec->f0A) {
                rec->f12 = rec->f0A;
                rec->f16 = rec->f0E - rec->f0A;
                UiSetSpritePos_28fd10(D_00484710, 0x7642, 0x1E,
                            rec->f02 + rec->f12 * rec->f06, 0);
            }
            normal_TransHunterRankListFill_51d820(rec->f16);
        } else {
            rec->f12 = rec->f0A;
            rec->f16 = rec->f0E - rec->f0A;
            UiSetSpritePos_28fd10(D_00484710, 0x7642, 0x1E,
                        rec->f02 + rec->f12 * rec->f06, 0);
        }
        if (rec->f16 < 0) {
            rec->f16 = 0;
        }
        UiMoveWidgetUniform_290f50(D_00484710, 0x7644, 0, (s32)((f32)rec->f16 * D_004848B8), D_0047D998, 0
);
    } else if ((D_00484720->f14 & 1) &&
               PadIsTriggered_1839f0(D_004B2570, 0x1000) != 0 &&
               PadIsRepeatTriggered_183dd0(D_004B2570, 0x1000) == 0) {
        if (rec->f12 == 0 && rec->f16 == 0 && rec->f0E > 0) {
            MenuGridCursorRequestSe_28e9e0(D_00484720, 0);
            rec->f12 = rec->f0A;
            rec->f16 = rec->f0E - rec->f0A;
            UiSetSpritePos_28fd10(D_00484710, 0x7642, 0x1E,
                        rec->f02 + rec->f12 * rec->f06, 0);
            normal_TransHunterRankListFill_51d820(rec->f16);
            UiSetWidgetPos_290f60(D_00484710, 0x7644, 0,
                        (s32)((f32)rec->f16 * D_004848B8));
        }
    } else if ((D_00484720->f14 & 2) &&
               PadIsTriggered_1839f0(D_004B2570, 0x4000) != 0 &&
               PadIsRepeatTriggered_183dd0(D_004B2570, 0x4000) == 0) {
        if (rec->f12 == rec->f0A && rec->f16 == rec->f0E - rec->f0A &&
            rec->f0E > 0) {
            MenuGridCursorRequestSe_28e9e0(D_00484720, 0);
            rec->f12 = 0;
            rec->f16 = 0;
            UiSetSpritePos_28fd10(D_00484710, 0x7642, 0x1E,
                        rec->f02 + rec->f12 * rec->f06, 0);
            normal_TransHunterRankListFill_51d820(rec->f16);
            UiSetWidgetPos_290f60(D_00484710, 0x7644, 0,
                        (s32)((f32)rec->f16 * D_004848B8));
        }
    }
    D_004848B4 = rec->f12;
    return 1;
}
