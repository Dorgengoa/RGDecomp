#include "types.h"

/* insmenu 0x004F30A0 (128 bytes) -- the close half of insmenu_InsectVsMenuDraw_4f3030,
 * same two-term `||` and the same screen hand-off, to func_436640.
 *
 * ★ The mode is tested against ZERO first and against 2 second, and both tests
 * are in the source: a bare `if (mode == 2)` needs only one compare.  The `== 0`
 * arm is the likely branch, so it is the one written as an early exit. */

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

typedef struct Screen Screen;

extern const u8 D_004FA180[];
extern u8 D_004842E8;           /* gp - 0xE88, passed by address */
extern s16 D_00484300;          /* gp - 0xE70 */
extern u8 D_00484360;           /* gp - 0xE10 */
extern Screen *D_00484104;      /* gp - 0x106C */

extern void func_2913A0(const void *a);
extern void func_28ED70(void *a);
extern Handle *func_1FEDE0(void);
extern void func_436640(Screen *s);

void insmenu_InsectVsMenuUpdate_4f30a0(void)
{
    Screen *scr;
    s16 mode;

    mode = D_00484300;
    if (mode == 0) {
        return;
    }
    if (mode == 2) {
        func_2913A0(D_004FA180);
        func_28ED70(&D_004842E8);
        if (func_1FEDE0()->field24->field1188->field08 == 0x25B || D_00484360) {
            scr = D_00484104;
            if (scr) {
                func_436640(scr);
            }
        }
    }
}
