/* rgp:protos */
#define RGP_SELF_MapBlockGetEntries_1dfd30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0xC0. */

typedef struct Obj_FUN_001dfd30 {
    u8 pad000[0xC0];
    s32 field;         /* +0xC0 */
} Obj_FUN_001dfd30;

s32 MapBlockGetEntries_1dfd30(Obj_FUN_001dfd30 *o)
{
    return o->field;
}
