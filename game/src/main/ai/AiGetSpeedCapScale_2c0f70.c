/* rgp:protos */
#define RGP_SELF_AiGetSpeedCapScale_2c0f70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the f32 at +0x284. */

typedef struct Obj_FUN_002c0f70 {
    u8 pad000[0x284];
    f32 field;         /* +0x284 */
} Obj_FUN_002c0f70;

f32 AiGetSpeedCapScale_2c0f70(Obj_FUN_002c0f70 *o)
{
    return o->field;
}
