#include "types.h"

/* Read the s16 at +0x4. */

typedef struct Obj_FUN_002e4780 {
    u8 pad000[0x4];
    s16 field;         /* +0x4 */
} Obj_FUN_002e4780;

s16 EventPathSegGetToIdx_2e4780(Obj_FUN_002e4780 *o)
{
    return o->field;
}
