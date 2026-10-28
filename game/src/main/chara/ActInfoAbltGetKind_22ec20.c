/* rgp:protos */
#define RGP_SELF_ActInfoAbltGetKind_22ec20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s16 at +0xA. */

typedef struct Obj_FUN_0022ec20 {
    u8 pad000[0xA];
    s16 field;         /* +0xA */
} Obj_FUN_0022ec20;

s16 ActInfoAbltGetKind_22ec20(Obj_FUN_0022ec20 *o)
{
    return o->field;
}
