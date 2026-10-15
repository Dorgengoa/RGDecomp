#include "types.h"

/* Read the u8 at +0x5E00. */

typedef struct Obj_FUN_001cebd0 {
    u8 pad000[0x5E00];
    u8 field;         /* +0x5E00 */
} Obj_FUN_001cebd0;

u8 GameSceneIsDoubleStepModeMaybe_1cebd0(Obj_FUN_001cebd0 *o)
{
    return o->field;
}
