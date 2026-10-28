/* rgp:protos */
#define RGP_SELF_EntryTableGetCurrent_323530 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0xC. */

typedef struct Obj_FUN_00323530 {
    u8 pad000[0xC];
    s32 field;         /* +0xC */
} Obj_FUN_00323530;

s32 EntryTableGetCurrent_323530(Obj_FUN_00323530 *o)
{
    return o->field;
}
