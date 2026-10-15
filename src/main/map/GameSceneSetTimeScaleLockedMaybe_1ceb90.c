#include "types.h"

/* Write the u8 at +0x5E14. */

typedef struct Obj_FUN_001ceb90 {
    u8 pad000[0x5E14];
    u8 field;         /* +0x5E14 */
} Obj_FUN_001ceb90;

void GameSceneSetTimeScaleLockedMaybe_1ceb90(Obj_FUN_001ceb90 *o, u8 value)
{
    o->field = value;
}
