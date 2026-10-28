/* rgp:protos */
#define RGP_SELF_AiSetApproachMarginMaybe_2c0f00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the f32 at +0x270. */

typedef struct Obj_FUN_002c0f00 {
    u8 pad000[0x270];
    f32 field;         /* +0x270 */
} Obj_FUN_002c0f00;

void AiSetApproachMarginMaybe_2c0f00(Obj_FUN_002c0f00 *o, f32 value)
{
    o->field = value;
}
