/* rgp:protos */
#define RGP_SELF_NavGraphGetNodeCount_310cb0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the u16 at +0xA8. */

typedef struct Obj_FUN_00310cb0 {
    u8 pad000[0xA8];
    u16 field;         /* +0xA8 */
} Obj_FUN_00310cb0;

u16 NavGraphGetNodeCount_310cb0(Obj_FUN_00310cb0 *o)
{
    return o->field;
}
