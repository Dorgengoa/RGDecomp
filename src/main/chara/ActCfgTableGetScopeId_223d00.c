#include "types.h"

/* Read the s16 at +0x12. */

typedef struct Obj_FUN_00223d00 {
    u8 pad000[0x12];
    s16 field;         /* +0x12 */
} Obj_FUN_00223d00;

s16 ActCfgTableGetScopeId_223d00(Obj_FUN_00223d00 *o)
{
    return o->field;
}
