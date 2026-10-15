#include "types.h"

/* Write the u8 at +0xC. */

typedef struct Obj_FUN_00345190 {
    u8 pad000[0xC];
    u8 field;         /* +0xC */
} Obj_FUN_00345190;

void HatenaMarkSetState_345190(Obj_FUN_00345190 *o, u8 value)
{
    o->field = value;
}
