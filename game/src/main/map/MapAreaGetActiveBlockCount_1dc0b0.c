/* rgp:protos */
#define RGP_SELF_MapAreaGetActiveBlockCount_1dc0b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s16 at +0x1CA. */

typedef struct Obj_FUN_001dc0b0 {
    u8 pad000[0x1CA];
    s16 field;         /* +0x1CA */
} Obj_FUN_001dc0b0;

s16 MapAreaGetActiveBlockCount_1dc0b0(Obj_FUN_001dc0b0 *o)
{
    return o->field;
}
