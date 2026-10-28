/* rgp:protos */
#define RGP_SELF_AiSetStopDistance_2c0ef0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the f32 at +0x274. */

typedef struct Obj_FUN_002c0ef0 {
    u8 pad000[0x274];
    f32 field;         /* +0x274 */
} Obj_FUN_002c0ef0;

void AiSetStopDistance_2c0ef0(Obj_FUN_002c0ef0 *o, f32 value)
{
    o->field = value;
}
