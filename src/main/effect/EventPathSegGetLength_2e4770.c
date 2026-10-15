#include "types.h"

/* Read the s16 at +0x6. */

typedef struct Obj_FUN_002e4770 {
    u8 pad000[0x6];
    s16 field;         /* +0x6 */
} Obj_FUN_002e4770;

s16 EventPathSegGetLength_2e4770(Obj_FUN_002e4770 *o)
{
    return o->field;
}
