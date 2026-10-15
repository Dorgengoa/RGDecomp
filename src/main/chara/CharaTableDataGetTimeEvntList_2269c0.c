#include "types.h"

/* Read the s32 at +0x8. */

typedef struct Obj_FUN_002269c0 {
    u8 pad000[0x8];
    s32 field;         /* +0x8 */
} Obj_FUN_002269c0;

s32 CharaTableDataGetTimeEvntList_2269c0(Obj_FUN_002269c0 *o)
{
    return o->field;
}
