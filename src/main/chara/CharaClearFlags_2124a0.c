#include "types.h"

/* Zero the s64 at +0x568. */

typedef struct Obj_FUN_002124a0 {
    u8 pad000[0x568];
    s64 field;         /* +0x568 */
} Obj_FUN_002124a0;

void CharaClearFlags_2124a0(Obj_FUN_002124a0 *o)
{
    o->field = 0;
}
