/* rgp:protos */
#define RGP_SELF_SoundSlotGetHandle_1d2150 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x18. */

typedef struct Obj_FUN_001d2150 {
    u8 pad000[0x18];
    s32 field;         /* +0x18 */
} Obj_FUN_001d2150;

s32 SoundSlotGetHandle_1d2150(Obj_FUN_001d2150 *o)
{
    return o->field;
}
