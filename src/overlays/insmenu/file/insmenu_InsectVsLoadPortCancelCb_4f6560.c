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

extern const u8 D_004FA180[];

extern u8  D_004842E8;      /* gp - 0xE88, passed by address */
extern s16 D_00484364;      /* gp - 0xE0C */
extern u8  D_00484370;      /* gp - 0xE00 */
extern u8  D_00484388;      /* gp - 0xDE8 */
extern f32 D_0047D240;      /* gp - 0x7F30 */
extern f32 D_0047D34C;      /* gp - 0x7E24 */
extern f32 D_0047D3C8;      /* gp - 0x7DA8 */
extern f32 D_0047D3CC;      /* gp - 0x7DA4 */

extern void insmenu_InsectVsSaveShowMsg_4f6e00(s32 a, s32 b, s32 c);
extern void insmenu_InsectVsLoadPortCursorBob_4f68d0(s16 a, s32 b, s32 c);
extern Handle *func_1FEDE0(void);
extern void func_290690(const void *a, s32 b, f32 x, f32 y, f32 z);
extern void func_290F50(const void *a, s32 b, s32 c, s32 d, s32 e, f32 t);
extern void func_28EDE0(void *a, s32 b, s32 c);

s32 insmenu_InsectVsLoadPortCancelCb_4f6560(Panel *pan)
{
    s32 kind;
    u8 ok;

    D_00484388 = 1;
    insmenu_InsectVsSaveShowMsg_4f6e00(-1, 0, -1);
    insmenu_InsectVsLoadPortCursorBob_4f68d0(pan->field12, 0, 0);
    kind = func_1FEDE0()->field24->field1188->field08;
    ok = 0;
    if (kind == 0x1F6) {
        ok = 1;
    } else if (kind == 0x1F7) {
        ok = 1;
    } else if (kind == 0x193) {
        ok = 1;
    }
    if (ok && (D_00484370 == 0)) {
        func_290690(D_004FA180, 0x88BA, 0.0f, D_0047D3C8, -1.0f);
        func_290F50(D_004FA180, 0x88BA, 0xC8, 0, 0, D_0047D34C);
        func_290690(D_004FA180, 0x88BC, 0.0f, D_0047D3C8, -1.0f);
        func_290F50(D_004FA180, 0x88C1, -0x12, 0xC, 0, D_0047D240);
        func_290F50(D_004FA180, 0x88C0, -0xF, 0xF, 0, D_0047D240);
        func_290690(D_004FA180, 0x88C1, 0.0f, D_0047D3CC, -1.0f);
        func_290690(D_004FA180, 0x88C0, 0.0f, D_0047D3CC, -1.0f);
        func_28EDE0(&D_004842E8, 0x88C6, 0);
    } else if (D_00484370 != 0) {
        D_00484364 = 1;
        func_28EDE0(&D_004842E8, 0x88CC, 0);
    } else {
        func_28EDE0(&D_004842E8, 0x88BB, 0);
    }
    return 1;
}
