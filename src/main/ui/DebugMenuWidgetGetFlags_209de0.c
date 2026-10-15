#include "types.h"

/* Read the u16 at +0x2A. */

typedef struct Obj_FUN_00209de0 {
    u8 pad000[0x2A];
    u16 field;         /* +0x2A */
} Obj_FUN_00209de0;

u16 DebugMenuWidgetGetFlags_209de0(Obj_FUN_00209de0 *o)
{
    return o->field;
}
