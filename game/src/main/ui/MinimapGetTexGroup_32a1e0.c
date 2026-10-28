/* rgp:protos */
#define RGP_SELF_MinimapGetTexGroup_32a1e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s16 at +0x10C. */

typedef struct Obj_FUN_0032a1e0 {
    u8 pad000[0x10C];
    s16 field;         /* +0x10C */
} Obj_FUN_0032a1e0;

s16 MinimapGetTexGroup_32a1e0(Obj_FUN_0032a1e0 *o)
{
    return o->field;
}
