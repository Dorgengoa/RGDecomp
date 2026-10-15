#include "types.h"

/* Write the f32 at +0x278. */

typedef struct Obj_FUN_002c0ee0 {
    u8 pad000[0x278];
    f32 field;         /* +0x278 */
} Obj_FUN_002c0ee0;

void AiSetRunDistance_2c0ee0(Obj_FUN_002c0ee0 *o, f32 value)
{
    o->field = value;
}
