/* rgp:protos */
#define RGP_SELF_AiGetStopDistance_2c0fb0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the f32 at +0x274. */

typedef struct Obj_FUN_002c0fb0 {
    u8 pad000[0x274];
    f32 field;         /* +0x274 */
} Obj_FUN_002c0fb0;

f32 AiGetStopDistance_2c0fb0(Obj_FUN_002c0fb0 *o)
{
    return o->field;
}
