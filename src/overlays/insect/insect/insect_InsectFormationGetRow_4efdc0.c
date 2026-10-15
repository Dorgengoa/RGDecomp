#include "types.h"
/* insect 0x004EFDC0 -- 20 bytes, 5 instructions. */

typedef struct Obj {
    u8 *f00;                        /* +0x00 */
} Obj;

u8 *insect_InsectFormationGetRow_4efdc0(Obj *o, s32 i)
{
    return o->f00 + i * 5;
}
