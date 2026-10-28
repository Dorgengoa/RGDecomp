/* rgp:protos */
#define RGP_SELF_LoaderSetWaitFrames_1cd5a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s32 at +0x8. */

typedef struct Obj_FUN_001cd5a0 {
    u8 pad000[0x8];
    s32 field;         /* +0x8 */
} Obj_FUN_001cd5a0;

void LoaderSetWaitFrames_1cd5a0(Obj_FUN_001cd5a0 *o, s32 value)
{
    o->field = value;
}
