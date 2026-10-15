#include "types.h"
/* insect 0x00514AC0 -- 52 bytes, 13 instructions.  ONE `&&`, not two early
 * returns: the two-`return 0` spelling folds the second test to `slti`+`xori`
 * (10 words); `&&` keeps retail's `bnez` to a shared `$2 = 0` (13 words). */

typedef struct Ent {
    u8  pad00[0x18];
    s8  f18;                        /* +0x18 */
    u8  pad19[0x22 - 0x19];
    u16 f22;                        /* +0x22 */
} Ent;

s32 insect_InsectPieceIsAce_514ac0(Ent *e)
{
    if (e->f18 >= 5 && e->f22 >= 0x2BC) {
        return 1;
    }
    return 0;
}
