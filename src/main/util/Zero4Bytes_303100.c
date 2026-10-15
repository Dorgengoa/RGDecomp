#include "types.h"

/* Zero the s32 at +0x0. */

typedef struct Obj_FUN_00303100 {
    s32 field;         /* +0x00 */
} Obj_FUN_00303100;

void Zero4Bytes_303100(Obj_FUN_00303100 *o)
{
    o->field = 0;
}
