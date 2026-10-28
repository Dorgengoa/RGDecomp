/* rgp:protos */
#define RGP_SELF_SoundSlotGetIndex_1d2140 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s16 at +0x1C. */

typedef struct Obj_FUN_001d2140 {
    u8 pad000[0x1C];
    s16 field;         /* +0x1C */
} Obj_FUN_001d2140;

s16 SoundSlotGetIndex_1d2140(Obj_FUN_001d2140 *o)
{
    return o->field;
}
