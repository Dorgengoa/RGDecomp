#include "types.h"
/* insect 0x004F0AD0 -- 47 instructions.  A three-arm switch that selects a u16
 * counter cell and bumps it; the pointer is initialised to 0 BEFORE the
 * handle call (it fills that call's delay slot) and the default arm really does
 * dereference the null.
 *
 * The compare chain runs 5, 4, 3 while the arm blocks are laid out 3, 4, 5, so
 * it is a `switch` with source case order 3, 4, 5 --
 * insect-dispatch-branch-polarity. */

typedef struct Ctx {
    u8    pad00[0x24];
    s32   m24;                      /* +0x24 */
} Ctx;

typedef struct Obj {
    u8  pad0000[0x5DA8];
    s32 m5DA8;                      /* +0x5DA8 */
} Obj;

extern Ctx *func_1FEDE0(void);
extern u8  *func_430B30(s32 k);
extern u8  *func_430B50(s32 k);
extern u8  *func_430B70(s32 k);

void insect_InsectBattleRecordAddWin_4f0ad0(Obj *o, s32 k)
{
    u16 *p;
    Ctx *h;
    u8  *b;

    p = 0;
    h = func_1FEDE0();
    switch (o->m5DA8) {
    case 3:
        p = (u16 *)(func_430B70(h->m24) + k * 2 + 0x4C8);
        break;
    case 4:
        b = func_430B50(h->m24);
        if (k == 0) {
            p = (u16 *)(b + 0x3E0);
        } else {
            p = (u16 *)(b + 0x3E2);
        }
        break;
    case 5:
        p = (u16 *)(func_430B30(h->m24) + k * 2 + 0x2EE);
        break;
    }
    *p += 1;
}
