/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsTopMenuStep_4edeb0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* insmenu 0x004EDEB0 (628 bytes, 157 instructions, 24 calls) -- the largest
 * member of the nine-function state-handler family, written from the matched
 * 0x004EDC50.  Frame 0x70, so `0x70($29)` is caller+0 = argument 9 and
 * `0x78($29)` is caller+8 = argument 10 (eight integer arguments go in
 * $4..$11, the rest in eight-byte stack slots from caller_sp+0).
 *
 * ★ The lookup is TWO arrays sharing one scaled index: `sll $4, $2, 3` is
 * computed once and added to both `%hi/%lo(insmenu_D_004F9A00)` and
 * `%hi/%lo(insmenu_D_004F9A04)`, so the source is two `[idx * 2]` reads of two `s32`
 * arrays four bytes apart, not one array of pairs.
 *
 * ★ `(u32)(a - 3) < 3` -- the unsigned range check written out.  Spelled as
 * `a >= 3 && a <= 5` mwcc emits two signed `slti`s and an `xori` instead.
 */

typedef struct Handle Handle;
struct Handle {
    u8 pad00[0x24];
    s32 field24;
};

typedef struct Rec Rec;
struct Rec {
    s32 field00;
    s32 field04;
};

typedef struct Panel Panel;
struct Panel {
    u8 pad00[0x12];
    s16 field12;
};

extern u8 insmenu_D_004FA1A0[];
extern u8 D_004B2570[];
extern s32 insmenu_D_004F9A00[];
extern s32 insmenu_D_004F9A04[];

extern u8 D_00484304;       /* gp - 0xE6C */
extern u8 D_0048430C;       /* gp - 0xE64 */

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

s32 insmenu_InsectVsTopMenuStep_4edeb0(s32 p1, s32 p2, s32 p3, s32 p4, s32 p5, s32 p6,
                          s32 p7, s32 p8, s32 code, s32 sub, s32 p11)
{
    Handle *hnd;
    Rec *slot;
    s32 mode;
    s16 idx;
    u8 hit;
    u8 near;

    if ((insmenu_InsectVsTwoPlayerPanelIsVisible_4f1b20() != 0) || (insmenu_InsectVsPwWatchPanelIsVisible_4f1050() != 0) ||
        (insmenu_InsectVsRegisterPanelIsVisible_4f2360() != 0) || (insmenu_InsectVsConfirmDialogIsVisible_4ee860() != 0)) {
        D_00484304 = 1;
        return 1;
    }
    if (D_0048430C == 0) {
        if (insmenu_InsectVsTitleBannerIsStill_4f2ea0() == 0) {
            D_00484304 = 1;
            return 1;
        }
        if (insmenu_InsectVsTopPanelIsHidden_4f2a70() != 0) {
            insmenu_InsectVsTopPanelOpen_4f2a30();
            insmenu_InsectVsTitleBannerSlideIn_4f2ef0();
            D_00484304 = 1;
            return 1;
        }
        D_00484304 = 0;
    } else {
        if (insmenu_InsectVsTopPanelIsOpaque_4f2b00() == 0) {
            D_00484304 = 1;
            return 1;
        }
        D_0048430C = 0;
        insmenu_InsectVsTopPanelFocus_4f2680();
        D_00484304 = 0;
        return 1;
    }

    hnd = ((Handle *)GetGameData_1fede0());
    slot = ((Rec *)RecordGetPayloadIfKind14_430b90(hnd->field24));
    mode = MenuGridCursorInput_28e170(insmenu_D_004FA1A0, D_004B2570, 4, 0);
    idx = ((Panel *)UiEntryListGetCurrentData_28ec60(insmenu_D_004FA1A0))->field12;
    if (idx >= 0) {
        if (idx < 5) {
            code = insmenu_D_004F9A00[idx * 2];
            sub = insmenu_D_004F9A04[idx * 2];
            slot->field00 = code;
            slot->field04 = sub;
        }
    }
    hit = 0;
    if (mode == 1) {
        near = 0;
        if ((u32)(code - 3) < 3) {
            near = 1;
        }
        if (near) {
            insmenu_InsectVsTopPanelDim_4f29c0();
            insmenu_InsectVsTopCursorFadeOut_4f28b0();
            insmenu_InsectVsConfirmDialogOpen_4ee7c0(5);
        } else if (code == 6) {
            RecordSetStateClamped_430db0(hnd->field24, 0xCA, 0);
            insmenu_InsectVsTitleBannerSlideOut_4f2ed0();
            insmenu_InsectVsTopPanelFadeOut_4f2b60();
        } else if (code == 7) {
            hit = 1;
        }
    } else if (mode == 2) {
        hit = 1;
        code = 7;
        sub = 0x46;
    }
    if (hit) {
        if (code == 7) {
            slot->field00 = code;
            slot->field04 = sub;
            insmenu_InsectVsTopPanelFocus_4f2680();
            insmenu_InsectVsTopPanelDim_4f29c0();
            insmenu_InsectVsTopCursorFadeOut_4f28b0();
            insmenu_InsectVsConfirmDialogOpen_4ee7c0(0x19);
        }
    }
    return 1;
}
