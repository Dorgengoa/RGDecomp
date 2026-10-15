#include "types.h"
/* insect 0x00512BA0 -- 72 bytes, 18 instructions, 1 call.  A seven-step
 * refresh loop over command ids 0xE..0x14. */

typedef struct Obj { u8 raw[4]; } Obj;

extern void insect_InsectPieceClearStatus_513340(Obj *o, s32 k);

void insect_InsectPieceClearActionStatus_512ba0(Obj *o)
{
    s32 i;

    for (i = 0xE; i < 0x15; i++) {
        insect_InsectPieceClearStatus_513340(o, i);
    }
}
