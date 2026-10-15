#include "types.h"

/* insmenu 0x004F3250 (140 bytes) -- raise the "menu ready" event once the save
 * machine reaches one of the two finished states.
 *
 * ★ The compare chain runs 0xF, 0xE, 0xC and the arms land 0xC, 0xE: a switch,
 * whose chain is the REVERSE of the source case order and whose blocks follow
 * the source order.  The 0xF case is empty and its `beql` carries the
 * epilogue's `ld $31`. */

typedef struct Handle Handle;
struct Handle {
    u8   pad00[0x24];
    void *field24;
};

extern u8 D_004842E8;           /* gp - 0xE88, passed by address */
extern u8 D_00484310;           /* gp - 0xE60 */

extern Handle *func_1FEDE0(void);
extern s32 func_430890(void *a);
extern void func_28EDE0(void *a, s32 id, s32 c);

s32 insmenu_InsectVsSaveScreenRequest_4f3250(void)
{
    s32 st;

    st = func_430890(func_1FEDE0()->field24);
    switch (st) {
    case 0xC:
        if (D_00484310 == 0) {
            func_28EDE0(&D_004842E8, 0x88B9, 1);
        }
        break;
    case 0xE:
        if (D_00484310 == 0) {
            func_28EDE0(&D_004842E8, 0x88B9, 1);
        }
        break;
    case 0xF:
        break;
    }
    return 1;
}
