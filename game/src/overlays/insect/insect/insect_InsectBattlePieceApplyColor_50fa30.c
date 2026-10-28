/* rgp:protos */
#define RGP_SELF_insect_InsectBattlePieceApplyColor_50fa30 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x0050FA30 -- 76 bytes, 19 instructions.
 * The first call reuses the `lb` that fed the 0x11 compare; the second
 * re-loads it, because the call may have written through the object. */

typedef struct Ent {
    u8  pad00[0x38];
    s8  f38;                        /* +0x38 */
    u8  pad39[0x58 - 0x39];
    s32 f58;                        /* +0x58 */
    u8  pad5C[0x68 - 0x5C];
    s32 f68;                        /* +0x68 */
} Ent;

/*rgp*/

void insect_InsectBattlePieceApplyColor_50fa30(s32 a, Ent *e)
{
    if (e->f38 == 0x11) {
        InsectModelApplyColorRec_3913f0(a, e->f38 + 0x7D0, e->f68);
        a = e->f58;
    }
    InsectModelApplyColorRec_3913f0(a, e->f38 + 0x7D0, e->f68);
}
