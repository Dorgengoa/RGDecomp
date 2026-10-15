#include "types.h"
/* insect 0x004E9F80 -- 20 bytes, 5 instructions.  `sltu $2,$0,$2` is the
 * `!= 0` boolean and `xori $2,$2,0x1` inverts it; the `andi $2,$2,0xFF` is the
 * u8 return type. */

typedef struct Obj {
    u8  pad00[0x190];
    s32 m190;                       /* +0x190 */
} Obj;

u8 insect_InsectSeqIsCmdIdle_4e9f80(Obj *o)
{
    return !o->m190;
}
