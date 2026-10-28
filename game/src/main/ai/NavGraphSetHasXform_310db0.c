/* rgp:protos */
#define RGP_SELF_NavGraphSetHasXform_310db0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the u8 at +0x113. */

typedef struct Obj_FUN_00310db0 {
    u8 pad000[0x113];
    u8 field;         /* +0x113 */
} Obj_FUN_00310db0;

void NavGraphSetHasXform_310db0(Obj_FUN_00310db0 *o, u8 value)
{
    o->field = value;
}
