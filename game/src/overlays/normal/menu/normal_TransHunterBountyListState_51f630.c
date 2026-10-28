/* rgp:protos */
#define RGP_SELF_normal_TransHunterBountyListState_51f630 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x0051F630 -- the 0x763C list's pad handler.  func_28E170 returns
 * 1 (confirm) / 2 (cancel) / 0 (idle); the idle arm is four D_004B2570 pad
 * tests (0x8000 up, 0x2000 down, 0x1000 and 0x4000 the shoulder jumps) that
 * move rec->f12 (the cursor row) and rec->f16 (the scroll offset) and repaint
 * the 0x7637 caret plus the 0x763E bar.  The `(s16)(rec->f0A + 1)` step is a
 * narrowed intermediate -- that dsll32/dsra32 pair is the page stride, and
 * the SECOND pair is the stored rec->f16 forwarded to its own sign test.
 *
 * s32/nc32e: MATCH.  The last 2 bad words were the branch at 0x51F780
 * (ours b .L0051FC00 + li $2,1 ; retail b .L0051FBFC + nop).  mwcc threads
 * only the FIRST predecessor of the shared `return 1' block, duplicating that
 * block's li into the delay slot and retargeting to +4.  Spelling the close
 * arm as an early `return 1;' kept it OUT of that block, so the code==1 arm
 * became the first predecessor and ate the threading.  Wrapping the rest in
 * an `else' so the close arm FALLS THROUGH to one tail `return 1;' makes
 * 0x51F690 the first predecessor again.  `goto done;' out of the close arm
 * gives the SAME object (35f2df73f3e6); adding explicit `return 1;' to the
 * code==1 / code==2 arms instead reads 4-6 bad. */

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

typedef struct Pad  { u8 pad00[0x14]; s32 f14; } Pad;
typedef struct Slot { u8 pad00[8]; s32 f08; } Slot;
typedef struct Inner { u8 pad000[0x180]; s32 f180; } Inner;
typedef struct Ent  { u8 pad00[0x18]; Inner *f18; } Ent;

extern u8 D_004B2570[];

extern Pad  *D_00484720;          /* gp - 0xA50  */
extern void *D_00484710;          /* gp - 0xA60  */
extern void *D_0048470C;          /* gp - 0xA64  */
extern s32   D_004848BC;          /* gp - 0x8B4  */
extern s16   D_004848C0;          /* gp - 0x8B0  */
extern f32   D_004848B8;          /* gp - 0x8B8  */
extern f32   D_0047D248;          /* gp - 0x7F28 */
extern f32   D_0047D9D4;          /* gp - 0x779C */

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
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_TransHunterBountyListState_51f630(void *unused, s32 close)
{
    s32   code;
    Rec  *rec;
    Ent  *e;
    Slot *sl;

    if (close != 0) {
        UiEntryListSelectByTag_28ea90(D_00484720, 9, 0);
        UiFadeWidgetAlpha_290690(D_00484710, 0x7637, D_0047D248, D_0047D9D4, -1.0f);
        UiFadeWidgetAlpha_290690(D_00484710, 0x764D, 1.0f, D_0047D9D4, -1.0f);
    } else {
        code = MenuGridCursorInput_28e170(D_00484720, D_004B2570, 0, 0);
        rec = ((Rec *)UiEntryListGetCurrentData_28ec60(D_00484720));
        if (code == 1) {
            e = ((Ent *)GetGameData_1fede0());
            sl = ((Slot *)UiGetWidgetSubItem_28f2b0(D_00484710, 0x763C, 0));
            if (sl == NULL) {
                return 0;
            }
            RankingCommitPoints_3e8b80(e, sl->f08);
            UiSetWidgetSubItemValue_291250(D_00484710, 0x763C, 1, (long long)(e->f18->f180));
            normal_TransHunterBountyMarkReported_51e480();
            StreamSetChanVolumeFade_1cd960(GetLoaderMgr_1f59d0(), 0, 0xF, 0.0f);
            StreamPlayMwv_207340(0x324, 0, 1.0f);
            RankingUpdateMaybe_3e8ce0(e);
            HunterBountyUpdateAll_3e9050(e, 0, 0, 0);
            D_004848BC = 3;
            D_004848C0 = 0x16;
            StateMachineSetState_28ede0(D_0048470C, 0x13, 0);
        } else if (code == 2) {
            StateMachineSetState_28ede0(D_0048470C, 0x12, 0);
        } else if (PadIsTriggered_1839f0(D_004B2570, 0x8000) != 0) {
            if (rec->f12 > 0 || rec->f16 > 0) {
                MenuGridCursorRequestSe_28e9e0(D_00484720, 0);
            }
            if (rec->f16 > 0) {
                rec->f16 = rec->f16 - (s16)(rec->f0A + 1);
                if (rec->f16 < 0) {
                    rec->f16 = 0;
                    rec->f12 = 0;
                    UiSetSpritePos_28fd10(D_00484710, 0x7637, 0x1E, rec->f02, 0);
                }
                normal_TransHunterBountyListFill_51efe0(rec->f16);
            } else {
                rec->f16 = 0;
                rec->f12 = 0;
                UiSetSpritePos_28fd10(D_00484710, 0x7637, 0x1E, rec->f02, 0);
            }
            if (rec->f16 < 0) {
                rec->f16 = 0;
            }
            UiMoveWidgetUniform_290f50(D_00484710, 0x763E, 0, (s32)((f32)rec->f16 * D_004848B8), D_0047D9D4, 0
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
                    UiSetSpritePos_28fd10(D_00484710, 0x7637, 0x1E,
                                rec->f02 + rec->f12 * rec->f06, 0);
                }
                normal_TransHunterBountyListFill_51efe0(rec->f16);
            } else {
                rec->f12 = rec->f0A;
                rec->f16 = rec->f0E - rec->f0A;
                UiSetSpritePos_28fd10(D_00484710, 0x7637, 0x1E,
                            rec->f02 + rec->f12 * rec->f06, 0);
            }
            if (rec->f16 < 0) {
                rec->f16 = 0;
            }
            UiMoveWidgetUniform_290f50(D_00484710, 0x763E, 0, (s32)((f32)rec->f16 * D_004848B8), D_0047D9D4, 0
);
        } else if ((D_00484720->f14 & 1) &&
                   PadIsTriggered_1839f0(D_004B2570, 0x1000) != 0 &&
                   PadIsRepeatTriggered_183dd0(D_004B2570, 0x1000) == 0) {
            if (rec->f12 == 0 && rec->f16 == 0 && rec->f0E > 0) {
                MenuGridCursorRequestSe_28e9e0(D_00484720, 0);
                rec->f12 = rec->f0A;
                rec->f16 = rec->f0E - rec->f0A;
                UiSetSpritePos_28fd10(D_00484710, 0x7637, 0x1E,
                            rec->f02 + rec->f12 * rec->f06, 0);
                normal_TransHunterBountyListFill_51efe0(rec->f16);
                UiSetWidgetPos_290f60(D_00484710, 0x763E, 0,
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
                UiSetSpritePos_28fd10(D_00484710, 0x7637, 0x1E,
                            rec->f02 + rec->f12 * rec->f06, 0);
                normal_TransHunterBountyListFill_51efe0(rec->f16);
                UiSetWidgetPos_290f60(D_00484710, 0x763E, 0,
                            (s32)((f32)rec->f16 * D_004848B8));
            }
        }
    }
    return 1;
}
