/* rgp:protos */
#define RGP_SELF_CharaActFlagsTurnBitsMaybe_20a590 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Mask the argument with 0x780. */

s32 CharaActFlagsTurnBitsMaybe_20a590(s32 x)
{
    return x & 0x780;
}
