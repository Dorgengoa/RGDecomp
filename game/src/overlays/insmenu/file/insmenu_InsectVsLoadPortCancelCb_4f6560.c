/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsLoadPortCancelCb_4f6560 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* insmenu 0x004F6560 (472 bytes, 118 instructions, 13 calls) -- open the map's
 * detail overlay for the entry the panel is on.
 *
 * ★ The three-term test is an if/else CHAIN with its own `ok = 1;` in each arm,
 * not `if (a || b || c) ok = 1;`.  The `||` form collapses to a single
 * assignment and comes out THREE WORDS short; a `switch` -- in either case
 * order, and with or without fall-through -- is one word short.  Each arm needs
 * its own store for mwcc to keep the per-term `b <join> / daddiu $4, $0, 1`
 * blocks retail has.
 * ★ `ok` is `u8` and tested bare, which is what gives `daddiu` rather than
 * `addiu` for the 1.
 */

typedef struct Panel Panel;
struct Panel {
    u8  pad00[0x12];
    s16 field12;
};

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

extern u8 insmenu_D_004FA180[];

extern u8  D_004842E8;      /* gp - 0xE88, passed by address */
extern s16 D_00484364;      /* gp - 0xE0C */
extern u8  D_00484370;      /* gp - 0xE00 */
extern u8  D_00484388;      /* gp - 0xDE8 */
extern f32 D_0047D240;      /* gp - 0x7F30 */
extern f32 D_0047D34C;      /* gp - 0x7E24 */
extern f32 D_0047D3C8;      /* gp - 0x7DA8 */
extern f32 D_0047D3CC;      /* gp - 0x7DA4 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 insmenu_InsectVsLoadPortCancelCb_4f6560(Panel *pan)
{
    s32 kind;
    u8 ok;

    D_00484388 = 1;
    insmenu_InsectVsSaveShowMsg_4f6e00(-1, 0, -1);
    insmenu_InsectVsLoadPortCursorBob_4f68d0(pan->field12, 0, 0);
    kind = ((Handle *)GetGameData_1fede0())->field24->field1188->field08;
    ok = 0;
    if (kind == 0x1F6) {
        ok = 1;
    } else if (kind == 0x1F7) {
        ok = 1;
    } else if (kind == 0x193) {
        ok = 1;
    }
    if (ok && (D_00484370 == 0)) {
        UiFadeWidgetAlpha_290690(insmenu_D_004FA180, 0x88BA, 0.0f, D_0047D3C8, -1.0f);
        UiMoveWidgetUniform_290f50(insmenu_D_004FA180, 0x88BA, 0xC8, 0, D_0047D34C, 0);
        UiFadeWidgetAlpha_290690(insmenu_D_004FA180, 0x88BC, 0.0f, D_0047D3C8, -1.0f);
        UiMoveWidgetUniform_290f50(insmenu_D_004FA180, 0x88C1, -0x12, 0xC, D_0047D240, 0);
        UiMoveWidgetUniform_290f50(insmenu_D_004FA180, 0x88C0, -0xF, 0xF, D_0047D240, 0);
        UiFadeWidgetAlpha_290690(insmenu_D_004FA180, 0x88C1, 0.0f, D_0047D3CC, -1.0f);
        UiFadeWidgetAlpha_290690(insmenu_D_004FA180, 0x88C0, 0.0f, D_0047D3CC, -1.0f);
        StateMachineSetState_28ede0(&D_004842E8, 0x88C6, 0);
    } else if (D_00484370 != 0) {
        D_00484364 = 1;
        StateMachineSetState_28ede0(&D_004842E8, 0x88CC, 0);
    } else {
        StateMachineSetState_28ede0(&D_004842E8, 0x88BB, 0);
    }
    return 1;
}
