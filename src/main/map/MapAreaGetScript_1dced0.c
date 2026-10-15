#include "types.h"

/* Read the s32 at +0xE8. */

typedef struct Obj_FUN_001dced0 {
    u8 pad000[0xE8];
    s32 field;         /* +0xE8 */
} Obj_FUN_001dced0;

s32 MapAreaGetScript_1dced0(Obj_FUN_001dced0 *o)
{
    return o->field;
}
