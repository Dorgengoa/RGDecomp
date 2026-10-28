/* rgp:protos */
#define RGP_SELF_SoundSlotGetVolume_1d2120 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the f32 at +0x20. */

typedef struct Obj_FUN_001d2120 {
    u8 pad000[0x20];
    f32 field;         /* +0x20 */
} Obj_FUN_001d2120;

f32 SoundSlotGetVolume_1d2120(Obj_FUN_001d2120 *o)
{
    return o->field;
}
