#include "types.h"

/* Read the s16 at +0x8. */

typedef struct Obj_FUN_003cd5b0 {
    u8 pad000[0x8];
    s16 field;         /* +0x8 */
} Obj_FUN_003cd5b0;

s16 StateGetChapter_3cd5b0(Obj_FUN_003cd5b0 *o)
{
    return o->field;
}
