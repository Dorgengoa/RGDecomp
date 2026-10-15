#include "types.h"

/* Read the s32 at +0x54. */

typedef struct Obj_FUN_00230250 {
    u8 pad000[0x54];
    s32 field;         /* +0x54 */
} Obj_FUN_00230250;

s32 CharaEffEntryGetName_230250(Obj_FUN_00230250 *o)
{
    return o->field;
}
