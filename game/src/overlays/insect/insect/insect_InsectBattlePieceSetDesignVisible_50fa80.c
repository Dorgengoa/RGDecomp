/* rgp:protos */
#define RGP_SELF_insect_InsectBattlePieceSetDesignVisible_50fa80 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x0050FA80 -- 44 bytes, 11 instructions.  A tail call whose first two
 * arguments are conditionally overwritten; `lw $4,0x58($5)` writes the
 * PARAMETER, so the source reassigns it. */

typedef struct Obj {
    u8  pad00[0x38];
    s8  f38;                        /* +0x38 */
    s8  f39;                        /* +0x39 */
    u8  pad3A[0x58 - 0x3A];
    s32 f58;                        /* +0x58 */
    u8  pad5C[0xE0 - 0x5C];
    s32 fE0;                        /* +0xE0 */
} Obj;

/*rgp*/

s32 insect_InsectBattlePieceSetDesignVisible_50fa80(s32 a, Obj *o, s32 k)
{
    s32 t;

    t = -1;
    if (o->f38 == 0x11) {
        a = o->f58;
    }
    if (k == 0) {
        t = o->f39;
    }
    return (ModelSetDesignVisible_391860(a, o->fE0, t), (s32)0);
}
