#include "types.h"

/* Write the s16 at +0x24. */

typedef struct Obj_FUN_003d5f50 {
    u8 pad000[0x24];
    s16 field;         /* +0x24 */
} Obj_FUN_003d5f50;

void OptionsSetTacticsMode_3d5f50(Obj_FUN_003d5f50 *o, s16 value)
{
    o->field = value;
}
