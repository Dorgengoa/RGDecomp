/* rgp:protos */
#define RGP_SELF_NavNodeGetFlags_3119a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0xC. */

typedef struct Obj_FUN_003119a0 {
    u8 pad000[0xC];
    s32 field;         /* +0xC */
} Obj_FUN_003119a0;

s32 NavNodeGetFlags_3119a0(Obj_FUN_003119a0 *o)
{
    return o->field;
}
