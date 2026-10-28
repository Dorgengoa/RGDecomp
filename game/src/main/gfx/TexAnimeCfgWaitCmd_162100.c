/* rgp:protos */
#define RGP_SELF_TexAnimeCfgWaitCmd_162100 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* D_00495E9C is reached with %hi/%lo, so it is an incomplete array, not a gp
   scalar.  The 8-byte cursor is post-incremented into the jal delay slot -
   the same idiom as the sibling VariantReadVec3_15f6c0. */

typedef struct Rec8 {
    u8 b[8];
} Rec8;

extern s16 D_00495E9C[];
/*rgp*/
/*rgp*/

s32 TexAnimeCfgWaitCmd_162100(Rec8 *p, s32 n)
{
    D_00495E9C[0] = (s16)VariantGetInt_15f780(p++);
    if (VariantGetInt_15f780(p++) != 0) {
        D_00495E9C[0] = -1;
    }
    if (n > 2) {
        SlotGetInt_15f720(p);
    }
    return 1;
}
