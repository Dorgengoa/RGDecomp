/* rgp:protos */
#define RGP_SELF_ParamTableGetRec_1cfbc0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* The accessor ParamTableSetAlpha_1cfb10 stores its float through -- same guard pair, a
   CONSTANT bound of 0xE0, and 0x18-byte records at +0x43A0. */

typedef struct Owner43A0 {
    u8 pad0000[0x43A0];
    u8 rec[1];         /* +0x43A0, 0x18 bytes each, 0xE0 of them */
} Owner43A0;

void *ParamTableGetRec_1cfbc0(Owner43A0 *o, s32 index)
{
    u8 ok;

    if (index < 0) {
        goto none;
    }
    ok = index < 0xE0;
    if (ok != 0) {
        goto found;
    }
none:
    return 0;
found:
    return &o->rec[index * 0x18];
}
