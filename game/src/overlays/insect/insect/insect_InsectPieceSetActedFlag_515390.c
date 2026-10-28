/* rgp:protos */
#define RGP_SELF_insect_InsectPieceSetActedFlag_515390 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00515390 -- 18 instructions.  Both calls take the same object and
 * the same 0x1C tag; the second is guarded by the second parameter. */

/*rgp*/
/*rgp*/

void insect_InsectPieceSetActedFlag_515390(u8 *p, s32 f)
{
    insect_InsectPieceClearStatus_513340(p, 0x1C);
    if (f != 0) {
        insect_InsectPieceSetStatus_5132d0(p, 0x1C);
    }
}
