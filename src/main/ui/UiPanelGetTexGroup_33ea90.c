#include "types.h"

/* Read the s32 at +0x18. */

typedef struct Obj_FUN_0033ea90 {
    u8 pad000[0x18];
    s32 field;         /* +0x18 */
} Obj_FUN_0033ea90;

s32 UiPanelGetTexGroup_33ea90(Obj_FUN_0033ea90 *o)
{
    return o->field;
}
