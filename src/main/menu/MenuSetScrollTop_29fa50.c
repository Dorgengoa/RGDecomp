#include "types.h"

/* Write the s16 at +0xFA. */

typedef struct Obj_FUN_0029fa50 {
    u8 pad000[0xFA];
    s16 field;         /* +0xFA */
} Obj_FUN_0029fa50;

void MenuSetScrollTop_29fa50(Obj_FUN_0029fa50 *o, s16 value)
{
    o->field = value;
}
