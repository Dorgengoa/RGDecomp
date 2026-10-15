#include "types.h"
/* insect 0x0051B8B0 -- 24 bytes, 6 instructions, a leaf with no frame.
 * `sltu $0,$2` + `xori 1` is the integer truthiness test `!x`; the trailing
 * `andi 0xFF` is the u8 return type.
 */

typedef struct Sub {
    u8  pad00[0x54];
    s8  m54;                        /* +0x54 */
} Sub;

typedef struct Obj {
    u8   pad00[4];
    Sub *m04;                       /* +0x04 */
} Obj;

u8 insect_InsectBattleLogIsEmpty_51b8b0(Obj *o)
{
    return !o->m04->m54;
}
