/* rgp:protos */
#define RGP_SELF_EvtGetSubMachine_26abb0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Asymmetric guard pair over the 0x20 sub-machines D_00482068 points at --
   the same 0x5F0-byte record EventSysUpdate_26ac10 walks, and the same
   pointer-in-small-data spelling. */

typedef struct Machine5F0 { u8 bytes[0x5F0]; } Machine5F0;

extern Machine5F0 *D_00482068;

void *EvtGetSubMachine_26abb0(s32 index)
{
    u8 ok;

    if (index < 0) {
        goto none;
    }
    ok = index < 0x20;
    if (ok != 0) {
        goto found;
    }
none:
    return 0;
found:
    return &D_00482068[index];
}
