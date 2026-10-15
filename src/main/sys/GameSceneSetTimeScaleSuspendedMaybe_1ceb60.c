#include "types.h"

/* Write the u8 at +0x5E15. */

typedef struct Obj_FUN_001ceb60 {
    u8 pad000[0x5E15];
    u8 field;         /* +0x5E15 */
} Obj_FUN_001ceb60;

void GameSceneSetTimeScaleSuspendedMaybe_1ceb60(Obj_FUN_001ceb60 *o, u8 value)
{
    o->field = value;
}
