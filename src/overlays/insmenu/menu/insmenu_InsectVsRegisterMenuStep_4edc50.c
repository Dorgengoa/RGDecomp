#include "types.h"

/* insmenu 0x004EDC50 (572 bytes, 143 instructions, 23 calls) -- member of the
 * nine-function state-handler family, written from the matched 0x004EC2A0.
 * Frame 0x60, so `0x68($29)` is caller+8 = argument 10 (eight integer
 * arguments go in $4..$11 and the rest in eight-byte stack slots).
 *
 * The opening guard is a FIVE-TERM `||`: the first test branches LIKELY to the
 * shared `D_00484304 = 1; return 1;` join duplicating its `addiu $2, $0, 1`,
 * the middle three take plain branches to the block that materialises it, and
 * the last falls through.  One `if` per call would have given five copies.
 *
 * `addiu $2, $20, -0x3C` + `sltiu $1, $2, 0x4` is the unsigned range check
 * WRITTEN OUT -- `(u32)(code - 0x3C) < 4`.  Spelled as the equivalent
 * `code >= 0x3C && code <= 0x3F` mwcc emits TWO signed `slti`s and an `xori`,
 * right length and six words wrong; it does not fold the pair into the
 * biased compare.
 */

typedef struct Handle Handle;
struct Handle {
    u8 pad00[0x24];
    s32 field24;
};

typedef struct Rec Rec;
struct Rec {
    u8  pad00[4];
    s32 field04;
};

typedef struct Panel Panel;
struct Panel {
    u8 pad00[0x12];
    s16 field12;
};

extern const u8 D_004FA1A0[];
extern const u8 D_004B2570[];
extern const s32 D_004F9A30[];

extern u8 D_00484304;       /* gp - 0xE6C */
extern u8 D_0048430C;       /* gp - 0xE64 */

extern s32 insmenu_InsectVsTopPanelIsVisible_4f2ac0(void);
extern s32 insmenu_InsectVsRegPwPanelIsVisible_4f0540(void);
extern s32 insmenu_InsectVsRegSavePanelIsVisible_4efc30(void);
extern s32 insmenu_InsectVsRegTeamPanelIsVisible_4ef0a0(void);
extern s32 insmenu_InsectVsConfirmDialogIsVisible_4ee860(void);
extern s32 insmenu_InsectVsTitleBannerIsStill_4f2ea0(void);
extern s32 insmenu_InsectVsRegisterPanelIsHidden_4f23a0(void);
extern void insmenu_InsectVsRegisterPanelOpen_4f2310(void);
extern void insmenu_InsectVsTitleBannerSlideIn_4f2ef0(void);
extern s32 insmenu_InsectVsRegisterPanelIsOpaque_4f23e0(void);
extern void insmenu_InsectVsRegisterPanelFocus_4f1f80(void);
extern Handle *func_1FEDE0(void);
extern Rec *func_430B90(s32 a);
extern s32 func_28E170(const void *a, const void *b, s32 c, s32 d);
extern Panel *func_28EC60(const void *a);
extern void insmenu_InsectVsRegisterPanelDim_4f22b0(void);
extern void insmenu_InsectVsRegisterCursorFadeOut_4f21b0(void);
extern void insmenu_InsectVsConfirmDialogOpen_4ee7c0(s32 a);
extern void func_430DB0(s32 a, s32 b);
extern void insmenu_InsectVsTitleBannerSlideOut_4f2ed0(void);
extern void insmenu_InsectVsRegisterPanelFadeOut_4f2440(void);
extern void insmenu_InsectVsMenuEnterRecordStep_4f2ab0(void);

s32 insmenu_InsectVsRegisterMenuStep_4edc50(s32 p1, s32 p2, s32 p3, s32 p4, s32 p5, s32 p6,
                          s32 p7, s32 p8, s32 p9, s32 code, s32 p11)
{
    Handle *hnd;
    Rec *slot;
    s32 mode;
    s16 idx;
    u8 hit;
    u8 near;

    if ((insmenu_InsectVsTopPanelIsVisible_4f2ac0() != 0) || (insmenu_InsectVsRegPwPanelIsVisible_4f0540() != 0) ||
        (insmenu_InsectVsRegSavePanelIsVisible_4efc30() != 0) || (insmenu_InsectVsRegTeamPanelIsVisible_4ef0a0() != 0) ||
        (insmenu_InsectVsConfirmDialogIsVisible_4ee860() != 0)) {
        D_00484304 = 1;
        return 1;
    }
    if (D_0048430C == 0) {
        if (insmenu_InsectVsTitleBannerIsStill_4f2ea0() == 0) {
            D_00484304 = 1;
            return 1;
        }
        if (insmenu_InsectVsRegisterPanelIsHidden_4f23a0() != 0) {
            insmenu_InsectVsRegisterPanelOpen_4f2310();
            insmenu_InsectVsTitleBannerSlideIn_4f2ef0();
            D_00484304 = 1;
            return 1;
        }
        D_00484304 = 0;
    } else {
        if (insmenu_InsectVsRegisterPanelIsOpaque_4f23e0() == 0) {
            D_00484304 = 1;
            return 1;
        }
        D_0048430C = 0;
        insmenu_InsectVsRegisterPanelFocus_4f1f80();
        D_00484304 = 0;
        return 1;
    }

    hnd = func_1FEDE0();
    slot = func_430B90(hnd->field24);
    mode = func_28E170(D_004FA1A0, D_004B2570, 4, 0);
    idx = func_28EC60(D_004FA1A0)->field12;
    if (idx >= 0) {
        if (idx < 5) {
            code = D_004F9A30[idx];
            slot->field04 = code;
        }
    }
    hit = 0;
    if (mode == 1) {
        near = 0;
        if ((u32)(code - 0x3C) < 4) {
            near = 1;
        }
        if (near) {
            insmenu_InsectVsRegisterPanelDim_4f22b0();
            insmenu_InsectVsRegisterCursorFadeOut_4f21b0();
            insmenu_InsectVsConfirmDialogOpen_4ee7c0(5);
        } else if (code == 0x40) {
            hit = 1;
        }
    } else if (mode == 2) {
        hit = 1;
        code = 0x40;
    }
    if (hit) {
        if (code == 0x40) {
            slot->field04 = code;
            insmenu_InsectVsRegisterPanelFocus_4f1f80();
            func_430DB0(hnd->field24, 0xC9);
            insmenu_InsectVsTitleBannerSlideOut_4f2ed0();
            insmenu_InsectVsRegisterPanelFadeOut_4f2440();
            insmenu_InsectVsMenuEnterRecordStep_4f2ab0();
        }
    }
    return 1;
}
