/* rgp:protos */
#define RGP_SELF_HpGaugeSetAlpha_31d1f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the f32 at +0x244. */

typedef struct Obj_FUN_0031d1f0 {
    u8 pad000[0x244];
    f32 field;         /* +0x244 */
} Obj_FUN_0031d1f0;

void HpGaugeSetAlpha_31d1f0(Obj_FUN_0031d1f0 *o, f32 value)
{
    o->field = value;
}
