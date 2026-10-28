/* rgp:protos */
#define RGP_SELF_ObjTypeMonographGetTouchTimer_372a80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the f32 at +0x104. */

typedef struct Obj_FUN_00372a80 {
    u8 pad000[0x104];
    f32 field;         /* +0x104 */
} Obj_FUN_00372a80;

f32 ObjTypeMonographGetTouchTimer_372a80(Obj_FUN_00372a80 *o)
{
    return o->field;
}
