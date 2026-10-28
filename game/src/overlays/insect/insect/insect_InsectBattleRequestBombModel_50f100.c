/* rgp:protos */
#define RGP_SELF_insect_InsectBattleRequestBombModel_50f100 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x0050F100 -- 19 instructions.  A tag guard then one call; the
 * data pointer is an overlay symbol well outside the gp window, so it takes a
 * %hi/%lo pair and the extern is `const`. */

typedef struct Obj {
    u8 pad00[0x38];
    s8 m38;                         /* +0x38 */
} Obj;

extern u8 insect_D_00525118[];
/*rgp*/
/*rgp*/

s32 insect_InsectBattleRequestBombModel_50f100(Obj *p)
{
    if (p->m38 != 0x11) {
        return 0;
    }
    insect_InsectFileSlotRequest_512140(InsectBattleGet_31a8d0() + 0x5000, insect_D_00525118, 2);
    return 1;
}
