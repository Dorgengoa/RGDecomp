/* rgp:protos */
#define RGP_SELF_EntryPosRecSetEntry_32b0a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s32 at +0xC. */

typedef struct Obj_FUN_0032b0a0 {
    u8 pad000[0xC];
    s32 field;         /* +0xC */
} Obj_FUN_0032b0a0;

void EntryPosRecSetEntry_32b0a0(Obj_FUN_0032b0a0 *o, s32 value)
{
    o->field = value;
}
