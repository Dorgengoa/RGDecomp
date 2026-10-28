/* rgp:protos */
#define RGP_SELF_MenuGetScrollTop_29fa40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s16 at +0xFA. */

typedef struct Obj_FUN_0029fa40 {
    u8 pad000[0xFA];
    s16 field;         /* +0xFA */
} Obj_FUN_0029fa40;

s16 MenuGetScrollTop_29fa40(Obj_FUN_0029fa40 *o)
{
    return o->field;
}
