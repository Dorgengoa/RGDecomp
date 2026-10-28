/* rgp:protos */
#define RGP_SELF_MapLinkGetTopY_1e92c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the f32 at +0x10. */

typedef struct Obj_FUN_001e92c0 {
    u8 pad000[0x10];
    f32 field;         /* +0x10 */
} Obj_FUN_001e92c0;

f32 MapLinkGetTopY_1e92c0(Obj_FUN_001e92c0 *o)
{
    return o->field;
}
