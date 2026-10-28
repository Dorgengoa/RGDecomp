/* rgp:protos */
#define RGP_SELF_MenuSetSwapSrc_29fa70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the u8 at +0x5E. */

typedef struct Obj_FUN_0029fa70 {
    u8 pad000[0x5E];
    u8 field;         /* +0x5E */
} Obj_FUN_0029fa70;

void MenuSetSwapSrc_29fa70(Obj_FUN_0029fa70 *o, u8 value)
{
    o->field = value;
}
