/* rgp:protos */
#define RGP_SELF_insect_InsectBattleIsSideDefeated_4f4670 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004F4670 -- 252 bytes, 63 instructions, 6 calls.
 * Two mutually exclusive scans over the 0x994-byte slot array at +0x35F8.
 */

typedef struct Slot {
    u8 pad00[0x994];
} Slot;

typedef struct Obj {
    u8   pad00[0x35F8];
    Slot f35F8[8];                  /* +0x35F8 */
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 insect_InsectBattleIsSideDefeated_4f4670(Obj *o, s32 a)
{
    Slot *e;
    void *p;
    s32 i;

    if (insect_InsectBattleTestFlag_50da40(o, 0x39) != 0) {
        for (i = 0; i < 2; i++) {
            if (insect_InsectTeamIsDefeated_5135f0(&o->f35F8[i], a) == 0) {
                return 0;
            }
        }
        return 1;
    }
    if (insect_InsectBattleTestFlag_50da40(o, 0x38) != 0) {
        e = &o->f35F8[a];
        for (i = 0; i < 5; i++) {
            p = insect_InsectTeamGetPiece_5138d0(e, i);
            if (p != 0) {
                if (insect_InsectPieceIsKing_514b00(p) != 0) {
                    if (insect_InsectPieceIsInPlay_5149e0(p) == 0) {
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}
