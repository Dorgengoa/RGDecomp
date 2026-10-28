/* rgp:protos */
#define RGP_SELF_CaptionCfgSetImageMode_33fe30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the u8 at +0x4E. */

typedef struct Obj_FUN_0033fe30 {
    u8 pad000[0x4E];
    u8 field;         /* +0x4E */
} Obj_FUN_0033fe30;

void CaptionCfgSetImageMode_33fe30(Obj_FUN_0033fe30 *o, u8 value)
{
    o->field = value;
}
