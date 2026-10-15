#include "types.h"

/* insmenu 0x004F2680 (396 bytes, 99 instructions) -- position the cursor
 * sprite for the current selection.  Mnemonic-identical twin of
 * `insmenu_FUN_004F1F80`; i_vars.py says FIFTEEN operand slots separate them.
 *
 * The code -> rank map is a real compiled `switch`: mwcc if-converts the first
 * four case bodies into the `beql` delay slots and leaves the four
 * `b <join> / nop` + `addiu $4, $0, K` blocks after the chain as dead code.
 * Written as an if/else chain the tail blocks do not appear.
 *
 * ★ CASE ORDER IS ASCENDING and case 0x3C carries an explicit `rank = 0;`.
 * Descending order, or an empty 0x3C body, both let mwcc delete the four dead
 * blocks -- 13 words SHORT.  The redundant `rank = 0` is what keeps them.
 *
 * ★ The first `func_290F60` argument reads `pan->field12` -- the field just
 * stored -- and NOT the `rank` local it was stored from.  mwcc forwards the
 * stored register and sign-extends it either way, so both spellings are 99
 * words; reading the local swaps the sign-extend and the `lh 0x6` between $3
 * and $7 and costs three words that only a byte compare sees.
 */

typedef struct Panel Panel;
struct Panel {
    s16 field00;
    s16 field02;
    u8  pad04[2];
    s16 field06;
    u8  pad08[2];
    s16 field0A;
    u8  pad0C[6];
    s16 field12;
};

typedef struct Handle Handle;
struct Handle {
    u8  pad00[0x24];
    s32 field24;
};

typedef struct Rec Rec;
struct Rec {
    s32 field00;
};

extern const u8 D_004FA180[];
extern const u8 D_004FA1A0[];

extern void func_28EA90(const void *a, s32 b, s32 c);
extern Panel *func_28EC60(const void *a);
extern Handle *func_1FEDE0(void);
extern Rec *func_430B90(s32 a);
extern void func_290F60(const void *a, s32 b, s32 c, s32 d);
extern void func_28FBF0(const void *a, s32 b, s32 c, s32 d);
extern void func_2907A0(const void *a, s32 b, f32 c);
extern void insmenu_InsectVsTopPanelBright_4f2950(void);
extern void insmenu_InsectVsTopCursorFadeIn_4f2900(void);

void insmenu_InsectVsTopPanelFocus_4f2680(void)
{
    Panel *pan;
    Rec *rec;
    s16 rank;

    func_28EA90(D_004FA1A0, 0x7531, 1);
    pan = func_28EC60(D_004FA1A0);
    pan->field0A = 4;
    rec = func_430B90(func_1FEDE0()->field24);
    rank = 0;
    if (rec != 0) {
        switch (rec->field00) {
        case 0x3:
            rank = 0;
            break;
        case 0x4:
            rank = 1;
            break;
        case 0x5:
            rank = 2;
            break;
        case 0x6:
            rank = 3;
            break;
        case 0x7:
            rank = 4;
            break;
        }
    }
    pan->field12 = rank;
    func_290F60(D_004FA180, 0x4, pan->field00, pan->field02 + (pan->field12 * pan->field06));
    func_290F60(D_004FA180, 0x2, 0, pan->field12 * pan->field06);
    if (pan->field12 < 4) {
        func_28FBF0(D_004FA180, 0x2, 0x126, 0);
    } else {
        func_28FBF0(D_004FA180, 0x2, 0x76, 0);
    }
    func_2907A0(D_004FA180, 0x2, 1.0f);
    insmenu_InsectVsTopPanelBright_4f2950();
    insmenu_InsectVsTopCursorFadeIn_4f2900();
}
