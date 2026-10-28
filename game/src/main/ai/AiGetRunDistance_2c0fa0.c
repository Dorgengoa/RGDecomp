/* rgp:protos */
#define RGP_SELF_AiGetRunDistance_2c0fa0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the f32 at +0x278. */

typedef struct Obj_FUN_002c0fa0 {
    u8 pad000[0x278];
    f32 field;         /* +0x278 */
} Obj_FUN_002c0fa0;

f32 AiGetRunDistance_2c0fa0(Obj_FUN_002c0fa0 *o)
{
    return o->field;
}
