/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsLoadConfirmCb_4f55c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* insmenu 0x004F55C0 (1416 bytes, 354 instructions) -- the insect-menu top
 * state machine.  `D_00484394` (gp - 0xDDC) is the state; the dispatch is a
 * five-arm compiled SWITCH (every arm is entered by a `beq`/`beql` INTO it and
 * the compare chain runs 4,3,2,1,0 -- i.e. reversed from the source order),
 * with the fall-through being the default.  Every arm ends in the shared
 * `return 1`.
 *
 * MEASURED, and the ONLY defect in the first draft (2 words LONG, 0x590 vs
 * 0x588, every other wrong word a pure -8 branch displacement): the widget id
 * carried across the nine-term `||` chain is an `s32` local NARROWED AT ITS
 * USE, `func_28EDE0(&D_004842E8, (u16)w, 0)` -- retail assigns it with a bare
 * `ori $16,$0,0x88BB` / `ori $16,$0,0x88C0` and masks once, `andi $5,$16,
 * 0xFFFF`, at the call.  Declaring the local `u16` instead masks at EVERY
 * ASSIGNMENT (`ori $3,$0,K` + `andi $16,$3,0xFFFF`), which is the two extra
 * words.  Note 0x88BB > 0x7FFF, so an s32 assignment still emits `ori`, not
 * `addiu` -- the constant's materialisation is unchanged by the widening.
 *
 * The switch compiles to a compare chain, not a jump table: the object has no
 * .rodata, no .lit4 and no .sdata, so this unit needs NO link plumbing.
 */

typedef struct Kind Kind;
struct Kind {
    u8  pad00[8];
    s32 field08;
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

extern u8 insmenu_D_004FA1A0[];
extern u8 D_004B2570[];
extern u8 D_004B27E0[];

extern s32 D_00484394;          /* gp - 0xDDC */
extern s32 D_00484398;          /* gp - 0xDD8 */
extern u8  D_00484344;          /* gp - 0xE2C */
extern u8  D_00484348;          /* gp - 0xE28 */
extern u8  D_004842E8;          /* gp - 0xE88, passed by address */

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
extern void memcpy(void *dst, void *src, s32 n);
/*rgp*/
/*rgp*/
/*rgp*/

s32 insmenu_InsectVsLoadConfirmCb_4f55c0(void)
{
    u8 buf[0x70] __attribute__((aligned(16)));
    Handle *hnd;
    s32 id;
    s32 st;
    s32 w;

    if (D_00484394 != 4 && D_00484394 != 3) {
        st = ((short)SaveGetResultStatus_37b970());
        if (SavePortCardIsReady_37b9b0(1) == 0 || st == 6 || st == 5 || st == 8) {
            insmenu_InsectVsSaveSetError_4f6e20(8);
            return 1;
        }
    }
    switch (D_00484394) {
    case 0:
        if (D_00484344 != 0) {
            insmenu_InsectVsSaveShowMsg_4f6e00(0x1F4, 0, -1);
            D_00484398 = 0;
            insmenu_InsectVsLoadYesNoCursorBob_4f69e0(0, 1, 0);
            SaveUiHideWidget_37b460(0x890D);
        } else {
            insmenu_InsectVsSaveShowMsg_4f6e00(0x15, 0, -1);
            D_00484398 = 0;
            insmenu_InsectVsLoadYesNoCursorBob_4f69e0(0, 1, 1);
            SaveUiHideWidget_37b460(0x890D);
        }
        D_00484394 = 1;
        break;
    case 1:
        if (D_00484344 != 0) {
            if (GetPauseStep_2f6660() != 0) {
                break;
            }
            if (PadIsTriggered_1839f0(D_004B2570, 0x60) != 0 ||
                (((unsigned char)IsPad2Enabled_2882c0()) != 0 && PadIsTriggered_1839f0(D_004B27E0, 0x60) != 0)) {
                D_00484344 = 0;
                insmenu_InsectVsSaveShowMsg_4f6e00(-1, 0, -1);
                PlayMenuSeThunk_289ef0(5);
                UiEntryListSelectByTag_28ea90(insmenu_D_004FA1A0, 0x88BB, 0);
            }
        } else {
            MenuYesNoCursorInput_377180(&D_00484398);
            insmenu_InsectVsLoadYesNoCursorBob_4f69e0(D_00484398, 0, 1);
            if (GetPauseStep_2f6660() != 0) {
                break;
            }
            if ((PadIsTriggered_1839f0(D_004B2570, 0x20) != 0 ||
                 (((unsigned char)IsPad2Enabled_2882c0()) != 0 && PadIsTriggered_1839f0(D_004B27E0, 0x20) != 0)) ||
                ((PadIsTriggered_1839f0(D_004B2570, 0x40) != 0 ||
                  (((unsigned char)IsPad2Enabled_2882c0()) != 0 && PadIsTriggered_1839f0(D_004B27E0, 0x40) != 0)) &&
                 D_00484398 == 1)) {
                insmenu_InsectVsLoadYesNoCursorBob_4f69e0(D_00484398, 0, 0);
                PlayMenuSeThunk_289ef0(6);
                insmenu_InsectVsSaveShowMsg_4f6e00(-1, 0, -1);
                UiEntryListSelectByTag_28ea90(insmenu_D_004FA1A0, 0x88BB, 0);
            } else if (PadIsTriggered_1839f0(D_004B2570, 0x40) != 0 ||
                       (((unsigned char)IsPad2Enabled_2882c0()) != 0 &&
                        PadIsTriggered_1839f0(D_004B27E0, 0x40) != 0)) {
                insmenu_InsectVsLoadYesNoCursorBob_4f69e0(D_00484398, 0, 0);
                PlayMenuSeThunk_289ef0(5);
                D_00484394 = 2;
            }
        }
        break;
    case 2:
        SaveMgrSetMode_37b9e0(5);
        insmenu_InsectVsSaveProgressWindowShow_4f6b90(2, 1);
        insmenu_InsectVsSaveShowMsg_4f6e00(7, 0, -1);
        D_00484394 = 3;
        break;
    case 3:
        if (((unsigned char)SaveModeChanged_37baa0()) == 0) {
            break;
        }
        insmenu_InsectVsSaveProgressWindowShow_4f6b90(2, 0);
        st = ((short)SaveGetResultStatus_37b970());
        if (st == 0) {
            if (SavePortCardIsReady_37b9b0(0) == 1) {
                PlayMenuSeThunk_289ef0(0x23);
                insmenu_InsectVsSaveShowMsg_4f6e00(0x16, 0, -1);
                SaveSysMsgGet_373840(((void)(insmenu_InsectVsGetSaveCtx_4f3850()), buf));
                memcpy(insmenu_InsectVsGetLoadSysMsgBuf_4f9700(), buf, 0x70);
                D_00484394 = 4;
                break;
            }
        }
        if (st == 5 || st == 6 || st == 8 || st == 2 || st == 3) {
            insmenu_InsectVsSaveSetError_4f6e20(0xE);
        } else if (st == 1) {
            insmenu_InsectVsSaveSetError_4f6e20(1);
        } else {
            insmenu_InsectVsSaveSetError_4f6e20(5);
        }
        break;
    case 4:
        if (GetPauseStep_2f6660() != 0) {
            break;
        }
        if (PadIsTriggered_1839f0(D_004B2570, 0x60) != 0 ||
            (((unsigned char)IsPad2Enabled_2882c0()) != 0 && PadIsTriggered_1839f0(D_004B27E0, 0x60) != 0)) {
            insmenu_InsectVsSaveShowMsg_4f6e00(-1, 0, -1);
            hnd = ((Handle *)GetGameData_1fede0());
            id = hnd->field24->field1188->field08;
            w = 0x88BB;
            if (id == 0x268 || id == 0x25D || id == 0x25A || id == 0x264 ||
                id == 0x26E || id == 0x278 || id == 0x1F6 || id == 0x1F7 ||
                id == 0x193) {
                w = 0x88C0;
            } else {
                D_00484348 = 1;
            }
            if (id == 0x26E) {
                RecordSetStateClamped_430db0(hnd->field24, 0x26F, 0);
            }
            StateMachineSetState_28ede0(&D_004842E8, (u16)w, 0);
        }
        break;
    }
    return 1;
}
