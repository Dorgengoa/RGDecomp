/* rgp:protos */
#define RGP_SELF_NavGraphGetMaxEdges_310bf0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the u16 at +0xBA. */

typedef struct Obj_FUN_00310bf0 {
    u8 pad000[0xBA];
    u16 field;         /* +0xBA */
} Obj_FUN_00310bf0;

u16 NavGraphGetMaxEdges_310bf0(Obj_FUN_00310bf0 *o)
{
    return o->field;
}
