#include "types.h"

/* insmenu 0x004EDA00 (492 bytes, 123 instructions, 19 calls) -- member of the
 * nine-function state-handler family; 0.943 mnemonic-similar to the matched
 * 0x004EC2A0, and written from it.
 *
 * Frame 0x50, so `0x60($29)` is caller+0x10 = argument 11 (mwcc's PS2 EABI
 * passes eight integer arguments in $4..$11 and the rest in eight-byte stack
 * slots from caller_sp+0).  Here argument 11 is the code itself; in 0x004EC2A0
 * the code is argument 10 and argument 11 is a separate pass-through.
 *
 * ★ `if (hit)` -- NOT `if (hit != 0)`.  A `u8` local tested with an explicit
 * `!= 0` makes mwcc re-normalise it with an `andi` at the READ; tested bare it
 * reads the register raw, which is what retail does.  One word, and it also
 * flips the guard above it from the LIKELY form to a plain branch plus `nop`
 * because the join loses its duplicable first instruction.
 *
 * The `mode == 1` arm RETURNS rather than falling through, so the join below
 * still has two predecessors and the branch stays plain.
 */

typedef struct Handle Handle;
struct Handle {
    u8 pad00[0x24];
    s32 field24;
};

typedef struct Obj Obj;
struct Obj {
    u8  pad00[0xE6];
    s16 fieldE6;
};

typedef struct Rec Rec;
struct Rec {
    s32 field00;
    u8  pad04[0xE8];
    s32 fieldEC;
};

typedef struct Panel Panel;
struct Panel {
    u8 pad00[0x12];
    s16 field12;
};

extern const u8 D_004FA1A0[];
extern const u8 D_004B2570[];
extern const s32 D_004F99B0[];

extern u8 D_00484304;       /* gp - 0xE6C */
extern u8 D_0048430C;       /* gp - 0xE64 */
extern Obj *D_00484104;     /* gp - 0x106C */

extern s32 insmenu_InsectVsRegisterPanelIsVisible_4f2360(void);
extern s32 insmenu_InsectVsConfirmDialogIsVisible_4ee860(void);
extern s32 insmenu_InsectVsTitleBannerIsStill_4f2ea0(void);
extern s32 insmenu_InsectVsRegPwPanelIsHidden_4f04f0(void);
extern void insmenu_InsectVsRegPwPanelOpen_4f04b0(void);
extern void insmenu_InsectVsBackGuideShow_4ea030(void);
extern void insmenu_InsectVsTitleBannerSlideIn_4f2ef0(void);
extern s32 insmenu_InsectVsRegPwPanelIsOpaque_4f0580(void);
extern void insmenu_InsectVsRegPwPanelFocus_4f00d0(void);
extern Handle *func_1FEDE0(void);
extern Rec *func_430B10(s32 a);
extern s32 func_28E170(const void *a, const void *b, s32 c, s32 d);
extern Panel *func_28EC60(const void *a);
extern void func_430DB0(s32 a, s32 b);
extern void insmenu_InsectVsRegPwPanelFadeOut_4f05e0(void);
extern void func_436450(Obj *a, s32 b);
extern void func_434410(Obj *a, s32 b, s32 c);
extern void func_4356D0(Obj *a, s32 b, void *c);
extern void insmenu_InsectVsRegPwPanelDim_4f0450(void);
extern void insmenu_InsectVsRegPwCursorFadeOut_4f0350(void);
extern void insmenu_InsectVsConfirmDialogOpen_4ee7c0(s32 a);

s32 insmenu_InsectVsRegPwMenuStep_4ece80(s32 p1, s32 p2, s32 p3, s32 p4, s32 p5, s32 p6,
                          s32 p7, s32 p8, s32 p9, s32 p10, s32 code)
{
    Handle *hnd;
    Rec *slot;
    s32 mode;
    s16 idx;
    u8 hit;

    if ((insmenu_InsectVsRegisterPanelIsVisible_4f2360() != 0) || (insmenu_InsectVsConfirmDialogIsVisible_4ee860() != 0)) {
        D_00484304 = 1;
        return 1;
    }
    if (D_0048430C == 0) {
        if (insmenu_InsectVsTitleBannerIsStill_4f2ea0() == 0) {
            D_00484304 = 1;
            return 1;
        }
        if (insmenu_InsectVsRegPwPanelIsHidden_4f04f0() != 0) {
            insmenu_InsectVsRegPwPanelOpen_4f04b0();
            insmenu_InsectVsBackGuideShow_4ea030();
            insmenu_InsectVsTitleBannerSlideIn_4f2ef0();
            D_00484304 = 1;
            return 1;
        }
        D_00484304 = 0;
    } else {
        if (insmenu_InsectVsRegPwPanelIsOpaque_4f0580() == 0) {
            D_00484304 = 1;
            return 1;
        }
        D_0048430C = 0;
        insmenu_InsectVsRegPwPanelFocus_4f00d0();
        D_00484304 = 0;
        return 1;
    }

    hnd = func_1FEDE0();
    slot = func_430B10(hnd->field24);
    mode = func_28E170(D_004FA1A0, D_004B2570, 4, 0);
    idx = func_28EC60(D_004FA1A0)->field12;
    if (idx >= 0) {
        if (idx < 4) {
            code = D_004F99B0[idx];
            slot->field00 = code;
        }
    }
    hit = 0;
    if (mode == 1) {
        func_430DB0(hnd->field24, code);
        insmenu_InsectVsRegPwPanelFadeOut_4f05e0();
        D_00484304 = 1;
        if (code == 0x25B) {
            if (D_00484104 != 0) {
                func_436450(D_00484104, 0);
                func_434410(D_00484104, 0x6D61, 1);
                D_00484104->fieldE6 = 0;
                func_4356D0(D_00484104, 0, &slot->fieldEC);
            }
        }
        return 1;
    }
    if (mode == 2) {
        hit = 1;
        code = 0x25F;
    }
    if (hit) {
        if (code == 0x25F) {
            slot->field00 = 0x25F;
            insmenu_InsectVsRegPwPanelDim_4f0450();
            insmenu_InsectVsRegPwCursorFadeOut_4f0350();
            insmenu_InsectVsConfirmDialogOpen_4ee7c0(0x1A);
        }
    }
    return 1;
}
