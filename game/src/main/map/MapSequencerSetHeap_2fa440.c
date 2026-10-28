/* rgp:protos */
#define RGP_SELF_MapSequencerSetHeap_2fa440 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s32 at +0x20. */

typedef struct Obj_FUN_002fa440 {
    u8 pad000[0x20];
    s32 field;         /* +0x20 */
} Obj_FUN_002fa440;

void MapSequencerSetHeap_2fa440(Obj_FUN_002fa440 *o, s32 value)
{
    o->field = value;
}
