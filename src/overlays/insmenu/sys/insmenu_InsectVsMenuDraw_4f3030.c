#include "types.h"

/* insmenu 0x004F3030 (112 bytes) -- while the menu is in mode 2, hand the
 * current screen to func_436610 provided the running scene is the insect lab
 * or the lab flag is set.
 *
 * ★ The two-term test is an `||`: retail's `beql` on the first term carries the
 * screen load in its delay slot, which is the join block's first instruction
 * duplicated into the likely slot -- the signature of a short-circuit merge and
 * not of two separate `if`s.
 * ★ The screen pointer is read into a named local, because retail loads it once
 * per arm and then tests the SAME register. */

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
extern s16 D_00484300;          /* gp - 0xE70 */
extern u8 D_00484360;           /* gp - 0xE10 */
extern Screen *D_00484104;      /* gp - 0x106C */

extern void func_291910(const void *a);
extern Handle *func_1FEDE0(void);
extern void func_436610(Screen *s);

void insmenu_InsectVsMenuDraw_4f3030(void)
{
    Screen *scr;

    if (D_00484300 == 2) {
        func_291910(D_004FA180);
        if (func_1FEDE0()->field24->field1188->field08 == 0x25B || D_00484360) {
            scr = D_00484104;
            if (scr) {
                func_436610(scr);
            }
        }
    }
}
