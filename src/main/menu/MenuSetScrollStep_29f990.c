#include "types.h"

/* Write the f32 at +0xF4. */

typedef struct Obj_FUN_0029f990 {
    u8 pad000[0xF4];
    f32 field;         /* +0xF4 */
} Obj_FUN_0029f990;

void MenuSetScrollStep_29f990(Obj_FUN_0029f990 *o, f32 value)
{
    o->field = value;
}
