/* rgp:protos */
#define RGP_SELF_NavGraphHasXform_310e60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s8 at +0x113. */

typedef struct Obj_FUN_00310e60 {
    u8 pad000[0x113];
    s8 field;         /* +0x113 */
} Obj_FUN_00310e60;

s8 NavGraphHasXform_310e60(Obj_FUN_00310e60 *o)
{
    return o->field;
}
