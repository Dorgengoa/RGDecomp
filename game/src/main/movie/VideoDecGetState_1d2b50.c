/* rgp:protos */
#define RGP_SELF_VideoDecGetState_1d2b50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0xA8. */

typedef struct Obj_FUN_001d2b50 {
    u8 pad000[0xA8];
    s32 field;         /* +0xA8 */
} Obj_FUN_001d2b50;

s32 VideoDecGetState_1d2b50(Obj_FUN_001d2b50 *o)
{
    return o->field;
}
