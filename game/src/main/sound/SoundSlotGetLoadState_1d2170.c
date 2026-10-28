/* rgp:protos */
#define RGP_SELF_SoundSlotGetLoadState_1d2170 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s16 at +0x2. */

typedef struct Obj_FUN_001d2170 {
    u8 pad000[0x2];
    s16 field;         /* +0x2 */
} Obj_FUN_001d2170;

s16 SoundSlotGetLoadState_1d2170(Obj_FUN_001d2170 *o)
{
    return o->field;
}
