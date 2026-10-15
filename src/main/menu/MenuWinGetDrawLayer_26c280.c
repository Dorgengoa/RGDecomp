#include "types.h"

/* Read the s32 at +0xBC. */

typedef struct Obj_FUN_0026c280 {
    u8 pad000[0xBC];
    s32 field;         /* +0xBC */
} Obj_FUN_0026c280;

s32 MenuWinGetDrawLayer_26c280(Obj_FUN_0026c280 *o)
{
    return o->field;
}
