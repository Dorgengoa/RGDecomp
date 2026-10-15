#include "types.h"

/* Read the s16 at +0xA. */

typedef struct Obj_FUN_003121c0 {
    u8 pad000[0xA];
    s16 field;         /* +0xA */
} Obj_FUN_003121c0;

s16 CharaRefGetId_3121c0(Obj_FUN_003121c0 *o)
{
    return o->field;
}
