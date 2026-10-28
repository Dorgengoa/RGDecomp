/* rgp:protos */
#define RGP_SELF_TrailRibbonHasVertexColor_32c800 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Is bit 0x40000000 of the s32 at +0x18 set? */

typedef struct Obj_FUN_0032c800 {
    u8 pad000[0x18];
    s32 flags;         /* +0x18 */
} Obj_FUN_0032c800;

u8 TrailRibbonHasVertexColor_32c800(Obj_FUN_0032c800 *o)
{
    u8 set;

    set = (o->flags & 0x40000000) != 0;
    return set;
}
