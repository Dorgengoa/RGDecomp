/* rgp:protos */
#define RGP_SELF_AiGetKeepDistanceMaybe_2c0f90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the f32 at +0x27C. */

typedef struct Obj_FUN_002c0f90 {
    u8 pad000[0x27C];
    f32 field;         /* +0x27C */
} Obj_FUN_002c0f90;

f32 AiGetKeepDistanceMaybe_2c0f90(Obj_FUN_002c0f90 *o)
{
    return o->field;
}
