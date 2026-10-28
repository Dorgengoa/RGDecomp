/* rgp:protos */
#define RGP_SELF_insect_InsectBattlePieceFlipMotionMaybe_50f2a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x0050F2A0 -- 164 bytes.  A three-arm if/else-if chain choosing a
 * (mode, extra) pair; only the LAST arm sets the follow-up flag, and it is set
 * in the `beql`'s delay slot.  The two float arguments go out through $f12/$f13
 * as `lui 0x3F80` + `mtc1`, i.e. plain literals, and the integer and float
 * argument pools are independent under the PS2 EABI. */
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void insect_InsectBattlePieceFlipMotionMaybe_50f2a0(void *o)
{
    s32 again;
    s32 extra;
    s32 mode;

    again = 0;
    extra = 0;
    if (insect_InsectPieceIsInPlay_5149e0(o) != 0) {
        if (insect_InsectPieceIsFlipped_514c30(o) != 0) {
            mode = 9;
        } else if (insect_InsectPieceIsDizzy_514c10(o) != 0) {
            mode = 4;
        } else {
            again = 1;
            mode = 0xA;
            extra = 6;
        }
        insect_InsectPiecePlayMotion_5145e0(o, mode, extra, 0.0f, 1.0f);
        if (again != 0) {
            insect_InsectBattlePieceResetMotion_50f960(o);
        }
    }
}
