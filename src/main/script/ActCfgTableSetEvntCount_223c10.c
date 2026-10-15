#include "types.h"

/* Write the s16 at +0x6E. */

typedef struct Obj_FUN_00223c10 {
    u8 pad000[0x6E];
    s16 field;         /* +0x6E */
} Obj_FUN_00223c10;

void ActCfgTableSetEvntCount_223c10(Obj_FUN_00223c10 *o, s16 value)
{
    o->field = value;
}
