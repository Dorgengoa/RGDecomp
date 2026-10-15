#include "types.h"

/* Write the s16 at +0x64. */

typedef struct Obj_FUN_00223c60 {
    u8 pad000[0x64];
    s16 field;         /* +0x64 */
} Obj_FUN_00223c60;

void ActCfgTableSetCallCount_223c60(Obj_FUN_00223c60 *o, s16 value)
{
    o->field = value;
}
