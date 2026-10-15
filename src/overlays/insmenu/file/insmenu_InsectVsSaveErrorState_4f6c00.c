#include "types.h"

/* insmenu 0x004F6C00 (504 bytes, 126 instructions, 20 calls).  ⚠ The flag it
 * branches on is `$5`, so it is the SECOND parameter and the first is unread;
 * m2c calls it `arg1`.
 *
 * The INNER dispatch is a compare chain; the OUTER one is a `switch`, and the
 * tell is the block order.  mwcc emits a switch's compare chain in REVERSE and
 * its case bodies in SOURCE order, so retail testing `== 1` first while laying
 * the `== 0` body out first is a switch written `case 0:` then `case 1:`.
 * As an `if (state == 1) ... else if (state == 0)` chain it is one word longer
 * and mwcc makes the `== 1` arm the fall-through.
 */

typedef struct Kind Kind;
struct Kind {
    u8  pad00[8];
    s16 field08;
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
extern const u8 D_004B2570[];
extern const u8 D_004B27E0[];

extern u8  D_004842E8;      /* gp - 0xE88, passed by address */
extern s16 D_00484384;      /* gp - 0xDEC */
extern s16 D_00484380;      /* gp - 0xDF0 */
extern f32 D_0047D3C8;      /* gp - 0x7DA8 */

extern void insmenu_InsectVsLoadYesNoCursorBob_4f69e0(s32 a, s32 b, s32 c);
extern void insmenu_InsectVsSaveProgressWindowShow_4f6b90(s32 a, s32 b);
extern void insmenu_InsectVsSaveShowMsg_4f6e00(s32 a, s32 b, s32 c);
extern s32  func_2F6660(void);
extern s32  func_1839F0(const void *a, s32 b);
extern s32  func_2882C0(void);
extern void insmenu_InsectVsLoadWidgetsFade_4f6ac0(s32 a);
extern void func_290690(const void *a, s32 b, f32 x, f32 y, f32 z);
extern void insmenu_InsectVsLoadPanelLayout_4f7dd0(void);
extern Handle *func_1FEDE0(void);
extern void func_430DB0(Ctx *a, s32 b);
extern void func_28EDE0(void *a, s32 b, s32 c);

s32 insmenu_InsectVsSaveErrorState_4f6c00(s32 p1, s32 open)
{
    Ctx *ctx;
    s16 kind;
    s16 state;

    if (open != 0) {
        D_00484384 = 0;
        insmenu_InsectVsLoadYesNoCursorBob_4f69e0(0, 1, 0);
        insmenu_InsectVsSaveProgressWindowShow_4f6b90(2, 0);
        state = D_00484380;
        if (state == 8) {
            insmenu_InsectVsSaveShowMsg_4f6e00(0xA, 0, -1);
        } else if (state == 5) {
            insmenu_InsectVsSaveShowMsg_4f6e00(0xB, 0, -1);
        } else if (state == 6) {
            insmenu_InsectVsSaveShowMsg_4f6e00(0xF, 0, -1);
        } else if (state == 0xE) {
            insmenu_InsectVsSaveShowMsg_4f6e00(0, 0, -1);
        } else if (state == 0x10) {
            insmenu_InsectVsSaveShowMsg_4f6e00(0x17, 0, -1);
        } else {
            insmenu_InsectVsSaveShowMsg_4f6e00(0xB, 0, -1);
        }
        return 1;
    }
    state = D_00484384;
    switch (state) {
    case 0:
        D_00484384 = 1;
        break;
    case 1:
        if ((func_2F6660() == 0) &&
            ((func_1839F0(D_004B2570, 0x60) != 0) ||
             ((func_2882C0() != 0) && (func_1839F0(D_004B27E0, 0x60) != 0)))) {
            insmenu_InsectVsSaveShowMsg_4f6e00(-1, 0, -1);
            insmenu_InsectVsLoadWidgetsFade_4f6ac0(2);
            func_290690(D_004FA180, 0x9CAA, 0.0f, D_0047D3C8, 0.0f);
            insmenu_InsectVsLoadPanelLayout_4f7dd0();
            ctx = func_1FEDE0()->field24;
            kind = ctx->field1188->field08;
            if (kind == 0x26F) {
                func_430DB0(ctx, 0x26E);
            } else if (kind == 0x279) {
                func_430DB0(ctx, 0x278);
            }
            func_28EDE0(&D_004842E8, 0x88BA, 0);
        }
        break;
    }
    return 1;
}
