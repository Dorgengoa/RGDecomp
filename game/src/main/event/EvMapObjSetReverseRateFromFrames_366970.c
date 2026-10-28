/* rgp:protos */
#define RGP_SELF_EvMapObjSetReverseRateFromFrames_366970 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Retail FALLS THROUGH into the -1.0f store, so that is the `if` body. */
void EvMapObjSetReverseRateFromFrames_366970(u8 *o, s32 n, s32 f)
{
    if (n <= 0) {
        *(f32 *)(o + 0x318) = -1.0f;
    } else {
        *(f32 *)(o + 0x318) = -1.0f / (f32)n;
    }
    *(u8 *)(o + 0x334) = !f;   /* `!x` on an int = sltu $0,x + xori 1; `x == 0` folds to xor+sltiu */
}
