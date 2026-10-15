#include "types.h"

/* Read the s16 at +0x0. */

typedef struct Obj_FUN_001de200 {
    s16 field;         /* +0x00 */
} Obj_FUN_001de200;

s16 MapPartTableGetId_1de200(Obj_FUN_001de200 *o)
{
    return o->field;
}
