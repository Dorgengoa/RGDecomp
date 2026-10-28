/* rgp:protos */
#define RGP_SELF_CharaGetHoverHeight_213dc0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the f32 at +0xA60. */

typedef struct Obj_FUN_00213dc0 {
    u8 pad000[0xA60];
    f32 field;         /* +0xA60 */
} Obj_FUN_00213dc0;

f32 CharaGetHoverHeight_213dc0(Obj_FUN_00213dc0 *o)
{
    return o->field;
}
