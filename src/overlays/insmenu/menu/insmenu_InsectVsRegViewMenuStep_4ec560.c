#include "types.h"

/* insmenu 0x004EC560 (480 bytes, 120 instructions, 18 calls) -- one of the
 * nine-member state-handler family (0x004EC2A0 / 0x004EC560 / 0x004EC9A0 /
 * 0x004ECE80 / 0x004ED260 / 0x004ED660 / 0x004EDA00 / 0x004EDC50 /
 * 0x004EDEB0), pairwise mnemonic similarity 0.80-1.00.
 *
 * ARGUMENTS: mwcc's PS2 EABI passes EIGHT integer arguments in $4..$11 and
 * puts the rest on the caller's stack in EIGHT-BYTE slots starting at
 * caller_sp+0.  Frame here is 0x60, so `0x68($29)` is caller+8 = argument 10
 * and `0x70($29)` is caller+0x10 = argument 11.  Measured with a probe TU
 * (p5..p11), not assumed.  Nine of the eleven parameters are unread.
 */

typedef struct Handle Handle;
struct Handle {
    u8 pad00[0x24];
    s32 field24;
};

typedef struct Panel Panel;
struct Panel {
    u8 pad00[0x12];
    s16 field12;
};

extern const u8 D_004FA1A0[];
extern const u8 D_004B2570[];
extern const s32 D_004F99D8[];

extern u8 D_00484304;       /* gp - 0xE6C */
extern u8 D_0048430C;       /* gp - 0xE64 */

extern s32 insmenu_InsectVsRegisterPanelIsVisible_4f2360(void);
extern s32 insmenu_InsectVsConfirmDialogIsVisible_4ee860(void);
extern s32 insmenu_InsectVsTitleBannerIsStill_4f2ea0(void);
extern s32 insmenu_InsectVsRegTeamPanelIsHidden_4ef050(void);
extern void insmenu_InsectVsRegViewPanelOpen_4ef010(void);
extern void insmenu_InsectVsBackGuideShow_4ea030(void);
extern void insmenu_InsectVsTitleBannerSlideIn_4f2ef0(void);
extern s32 insmenu_InsectVsRegTeamPanelIsOpaque_4ef0e0(void);
extern void insmenu_InsectVsRegViewPanelFocus_4eec60(void);
extern Handle *func_1FEDE0(void);
extern s32 *func_430AD0(s32 a);
extern s32 func_28E170(const void *a, const void *b, s32 c, s32 d);
extern Panel *func_28EC60(const void *a);
extern void func_430DB0(s32 a, s32 b);
extern void insmenu_InsectVsRegTeamPanelFadeOut_4ef140(void);
extern void insmenu_InsectVsRegTeamCursorFadeOut_4eee70(void);
extern void insmenu_InsectVsRegTeamPanelDim_4eef70(void);
extern void insmenu_InsectVsConfirmDialogOpen_4ee7c0(s32 a);

s32 insmenu_InsectVsRegViewMenuStep_4ec560(s32 p1, s32 p2, s32 p3, s32 p4, s32 p5, s32 p6,
                          s32 p7, s32 p8, s32 p9, s32 code, s32 arg)
{
    Handle *hnd;
    Panel *pan;
    s32 *slot;
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
        if (insmenu_InsectVsRegTeamPanelIsHidden_4ef050() != 0) {
            insmenu_InsectVsRegViewPanelOpen_4ef010();
            insmenu_InsectVsBackGuideShow_4ea030();
            insmenu_InsectVsTitleBannerSlideIn_4f2ef0();
            D_00484304 = 1;
            return 1;
        }
        D_00484304 = 0;
    } else {
        if (insmenu_InsectVsRegTeamPanelIsOpaque_4ef0e0() == 0) {
            D_00484304 = 1;
            return 1;
        }
        D_0048430C = 0;
        insmenu_InsectVsRegViewPanelFocus_4eec60();
        D_00484304 = 0;
        return 1;
    }

    hnd = func_1FEDE0();
    slot = func_430AD0(hnd->field24);
    mode = func_28E170(D_004FA1A0, D_004B2570, 4, 0);
    idx = func_28EC60(D_004FA1A0)->field12;
    if (idx >= 0) {
        if (idx < 2) {
            code = D_004F99D8[idx];
            *slot = code;
        }
    }
    hit = 0;
    if (mode == 1) {
        func_430DB0(hnd->field24, arg);
        insmenu_InsectVsRegTeamPanelFadeOut_4ef140();
        D_00484304 = 1;
        if (code == 0x270) {
            hit = 1;
        }
    } else if (mode == 2) {
        hit = 1;
        code = 0x270;
    }
    if (hit) {
        if (code == 0x270) {
            *slot = 0x270;
            insmenu_InsectVsRegTeamCursorFadeOut_4eee70();
            insmenu_InsectVsRegTeamPanelDim_4eef70();
            insmenu_InsectVsConfirmDialogOpen_4ee7c0(0x1A);
        }
    }
    return 1;
}
