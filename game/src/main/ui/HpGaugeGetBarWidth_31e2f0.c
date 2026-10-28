/* rgp:protos */
#define RGP_SELF_HpGaugeGetBarWidth_31e2f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s16 at +0x220. */

typedef struct Obj_FUN_0031e2f0 {
    u8 pad000[0x220];
    s16 field;         /* +0x220 */
} Obj_FUN_0031e2f0;

s16 HpGaugeGetBarWidth_31e2f0(Obj_FUN_0031e2f0 *o)
{
    return o->field;
}
