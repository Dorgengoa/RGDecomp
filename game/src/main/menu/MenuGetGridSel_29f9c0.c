/* rgp:protos */
#define RGP_SELF_MenuGetGridSel_29f9c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Address of the sub-object at +0x60. */

typedef struct Obj_FUN_0029f9c0 {
    u8 pad000[0x60];
    u8 sub[1];         /* +0x60 */
} Obj_FUN_0029f9c0;

void *MenuGetGridSel_29f9c0(Obj_FUN_0029f9c0 *o)
{
    return o->sub;
}
