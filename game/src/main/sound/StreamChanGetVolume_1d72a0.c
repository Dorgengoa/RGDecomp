/* rgp:protos */
#define RGP_SELF_StreamChanGetVolume_1d72a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the f32 at +0x84. */

typedef struct Obj_FUN_001d72a0 {
    u8 pad000[0x84];
    f32 field;         /* +0x84 */
} Obj_FUN_001d72a0;

f32 StreamChanGetVolume_1d72a0(Obj_FUN_001d72a0 *o)
{
    return o->field;
}
