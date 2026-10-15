#include "types.h"

/* Write the u8 at +0x5F. */

typedef struct Obj_FUN_0029fa60 {
    u8 pad000[0x5F];
    u8 field;         /* +0x5F */
} Obj_FUN_0029fa60;

void MenuSetSwapDst_29fa60(Obj_FUN_0029fa60 *o, u8 value)
{
    o->field = value;
}
