/* rgp:protos */
#define RGP_SELF_Vec4VectorClear_250970 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Zero the s32 at +0x4. */

typedef struct Obj_FUN_00250970 {
    u8 pad000[0x4];
    s32 field;         /* +0x4 */
} Obj_FUN_00250970;

void Vec4VectorClear_250970(Obj_FUN_00250970 *o)
{
    o->field = 0;
}
