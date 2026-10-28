/* rgp:protos */
#define RGP_SELF_insect_InsectBattlePlayBankSe_5107d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x005107D0 -- 80 bytes, 20 instructions, 3 calls.  The root handle is
 * fetched FIRST (the parameter copy sits in that call's delay slot), then two
 * nested guards gate the forward.  Both guards fall out to the shared
 * epilogue, so neither is an early return.
 */

typedef struct Root { u8 raw[4]; } Root;

/*rgp*/
/*rgp*/
/*rgp*/

void insect_InsectBattlePlayBankSe_5107d0(s32 id)
{
    Root *r;

    r = ((Root *)InsectBattleGet_31a8d0());
    if (id != -1) {
        if (r != 0) {
            SoundPlayDefault_1b9ae0(insect_InsectBattleGetSoundBank_50db50(r), id, 0);
        }
    }
}
