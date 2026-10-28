/* rgp:protos */
#define RGP_SELF_HpGaugeGetMode_31d3c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s8 at +0x240. */

typedef struct Obj_FUN_0031d3c0 {
    u8 pad000[0x240];
    s8 field;         /* +0x240 */
} Obj_FUN_0031d3c0;

s8 HpGaugeGetMode_31d3c0(Obj_FUN_0031d3c0 *o)
{
    return o->field;
}
