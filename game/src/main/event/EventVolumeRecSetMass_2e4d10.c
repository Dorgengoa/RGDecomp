/* rgp:protos */
#define RGP_SELF_EventVolumeRecSetMass_2e4d10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the f32 at +0x24. */

typedef struct Obj_FUN_002e4d10 {
    u8 pad000[0x24];
    f32 field;         /* +0x24 */
} Obj_FUN_002e4d10;

void EventVolumeRecSetMass_2e4d10(Obj_FUN_002e4d10 *o, f32 value)
{
    o->field = value;
}
