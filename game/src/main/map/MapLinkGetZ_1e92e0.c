/* rgp:protos */
#define RGP_SELF_MapLinkGetZ_1e92e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the f32 at +0xC. */

typedef struct Obj_FUN_001e92e0 {
    u8 pad000[0xC];
    f32 field;         /* +0xC */
} Obj_FUN_001e92e0;

f32 MapLinkGetZ_1e92e0(Obj_FUN_001e92e0 *o)
{
    return o->field;
}
