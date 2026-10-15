#include "types.h"

/* Zero the s32 at +0x3CCC. */

typedef struct Obj_FUN_00148030 {
    u8 pad000[0x3CCC];
    s32 field;         /* +0x3CCC */
} Obj_FUN_00148030;

void DrawCtxClearClipRangeSetMaybe_148030(Obj_FUN_00148030 *o)
{
    o->field = 0;
}
