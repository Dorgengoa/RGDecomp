#include "types.h"

/* Read the s8 at +0x4E. */

typedef struct Obj_FUN_0033fe20 {
    u8 pad000[0x4E];
    s8 field;         /* +0x4E */
} Obj_FUN_0033fe20;

s8 CaptionCfgGetImageMode_33fe20(Obj_FUN_0033fe20 *o)
{
    return o->field;
}
