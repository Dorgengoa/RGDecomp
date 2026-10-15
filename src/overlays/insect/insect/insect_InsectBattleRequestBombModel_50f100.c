#include "types.h"
/* insect 0x0050F100 -- 19 instructions.  A tag guard then one call; the
 * data pointer is an overlay symbol well outside the gp window, so it takes a
 * %hi/%lo pair and the extern is `const`. */

typedef struct Obj {
    u8 pad00[0x38];
    s8 m38;                         /* +0x38 */
} Obj;

extern const u8 D_00525118[];
extern s32 func_31A8D0(void);
extern void insect_InsectFileSlotRequest_512140(s32 a, const u8 *b, s32 c);

s32 insect_InsectBattleRequestBombModel_50f100(Obj *p)
{
    if (p->m38 != 0x11) {
        return 0;
    }
    insect_InsectFileSlotRequest_512140(func_31A8D0() + 0x5000, D_00525118, 2);
    return 1;
}
