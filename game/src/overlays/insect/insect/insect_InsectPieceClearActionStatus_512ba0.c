/* rgp:protos */
#define RGP_SELF_insect_InsectPieceClearActionStatus_512ba0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00512BA0 -- 72 bytes, 18 instructions, 1 call.  A seven-step
 * refresh loop over command ids 0xE..0x14. */

typedef struct Obj { u8 raw[4]; } Obj;

/*rgp*/

void insect_InsectPieceClearActionStatus_512ba0(Obj *o)
{
    s32 i;

    for (i = 0xE; i < 0x15; i++) {
        insect_InsectPieceClearStatus_513340(o, i);
    }
}
