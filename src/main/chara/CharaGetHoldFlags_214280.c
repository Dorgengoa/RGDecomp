#include "types.h"

/* Read the s64 at +0x578. */

typedef struct Obj_FUN_00214280 {
    u8 pad000[0x578];
    s64 field;         /* +0x578 */
} Obj_FUN_00214280;

s64 CharaGetHoldFlags_214280(Obj_FUN_00214280 *o)
{
    return o->field;
}
