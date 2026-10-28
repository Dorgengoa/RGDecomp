/* rgp:protos */
#define RGP_SELF_insect_InsectPieceIsEnemyOf_5149b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x005149B0 -- 36 bytes, 9 instructions.
 * `xor` + `sltu $0,x` is the `!=` of two loaded bytes. */

typedef struct Obj {
    u8 pad00[0x71];
    s8 f71;                         /* +0x71 */
} Obj;

s32 insect_InsectPieceIsEnemyOf_5149b0(Obj *a, Obj *b)
{
    if (b == 0) {
        return 0;
    }
    return a->f71 != b->f71;
}
