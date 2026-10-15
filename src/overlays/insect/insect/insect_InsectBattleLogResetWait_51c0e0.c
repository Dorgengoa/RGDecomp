#include "types.h"
/* insect 0x0051C0E0 -- 12 bytes, 3 instructions. */

typedef struct Obj {
    u8  pad00[0x1C];
    s16 f1C;                        /* +0x1C */
    u8  pad1E[0x20 - 0x1E];
    s16 f20;                        /* +0x20 */
} Obj;

void insect_InsectBattleLogResetWait_51c0e0(Obj *o)
{
    o->f20 = o->f1C;
}
