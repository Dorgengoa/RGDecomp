#include "types.h"

/* Read the s64 at +0x0. */

typedef struct Obj_FUN_00223ce0 {
    s64 field;         /* +0x00 */
} Obj_FUN_00223ce0;

s64 ActCfgTableGetFlags64_223ce0(Obj_FUN_00223ce0 *o)
{
    return o->field;
}
