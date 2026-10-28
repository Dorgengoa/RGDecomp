/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsMenuStateCtrlSetClose_4eaa80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* insmenu 0x004EAA80 (296 bytes, 74 instructions) -- the map/insect fade-gate
 * tick.  `func_290770(insmenu_D_004FA180, 0xA) <= 0.0f` is the fade guard and retail
 * FALLS THROUGH into the work, so the guard is written positive with the whole
 * body nested and the shared `return 1` after it.
 *
 * BATCHED loads-then-stores is ONE SUB-STRUCT ASSIGNMENT.  Retail emits
 * `lbu 0x4C6 / lbu 0x4C7 / sb -0xE5C / sb -0xE5B`, i.e. both loads before both
 * stores; written as two scalar assignments mwcc interleaves them and the unit
 * is 2 wrong words.  Declaring the 0x4C6/0x4C7 pair as a member struct and the
 * gp pair as the same struct closes it.  (`struct { u8 x, y; }`,
 * `struct { u8 v[2]; }` and a `*(Pair *)` cast onto the u8[2] array all give
 * the IDENTICAL object; two named temporaries do NOT -- 4 bad words.)
 *
 * `a` and `b` are `s32`, not `u8`: a u8 local costs an `andi ..,0xFF` at the
 * READ at every widening comparison (three of them here, exactly the 3 words
 * the draft was long).  `hit` stays `u8` because that is what gives retail's
 * `daddiu $17, $0, 1`, and it is tested BARE -- [[im-bare-flag-test]].
 *
 * `beq $18,$2` INTO the shared block then `bne $17,$2` PAST it is an `||`.
 * Declaration order of the six locals is a measured NULL here: nine orders,
 * one identical object.
 */

typedef struct Handle Handle;
struct Handle {
    u8  pad00[0x24];
    s32 field24;
};

typedef struct Pair Pair;
struct Pair {
    u8 x;
    u8 y;
};

typedef struct Rec Rec;
struct Rec {
    u8 pad000[0x4];
    u8 field004;
    u8 pad005[0x4C1];
    Pair field4C6;
};

extern u8 insmenu_D_004FA180[];

extern u8 D_00484304;       /* gp - 0xE6C */
extern Pair D_00484314;     /* gp - 0xE5C */

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

s32 insmenu_InsectVsMenuStateCtrlSetClose_4eaa80(void)
{
    Handle *hnd;
    Rec *rec;
    u8 hit;
    s32 a;
    s32 b;
    s32 code;

    D_00484304 = 1;
    if (UiGetWidgetAlpha_290770(insmenu_D_004FA180, 0xA) <= 0.0f) {
        hnd = ((Handle *)GetGameData_1fede0());
        RecordSetStateClamped_430db0(hnd->field24, 0x12D, 0);
        hit = 1;
        if (insmenu_InsectVsTakeCancelFlag_4ea0d0()) {
            rec = ((Rec *)RecordGetPayloadIfKind1E_430b70(hnd->field24));
            if (rec->field004 & 1) {
                D_00484314 = rec->field4C6;
            } else {
                hit = 0;
            }
        }
        if (hit) {
            a = D_00484314.x;
            b = D_00484314.y;
            if (a == 0) {
                if (b == 0) {
                    code = 1;
                } else {
                    code = 2;
                }
            } else {
                if (b == 0) {
                    code = 3;
                } else {
                    code = 4;
                }
            }
            RecordSetSubState_430bd0(hnd->field24, code);
            if ((a == 1) || (b == 1)) {
                SetPad2Enabled_2882b0();
            } else {
                ClearPad2Enabled_2882a0();
            }
        }
        insmenu_InsectVsMenuEnterRecordStep_4f1b10();
        insmenu_InsectVsTwoPlayerPanelFocus_4f16a0();
        insmenu_InsectVsTwoPlayerPanelHide_4f1ba0();
    }
    return 1;
}
