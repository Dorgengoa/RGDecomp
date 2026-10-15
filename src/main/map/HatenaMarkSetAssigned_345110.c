#include "types.h"

/* Write the u8 at +0xA8. */

typedef struct Obj_FUN_00345110 {
    u8 pad000[0xA8];
    u8 field;         /* +0xA8 */
} Obj_FUN_00345110;

void HatenaMarkSetAssigned_345110(Obj_FUN_00345110 *o, u8 value)
{
    o->field = value;
}
