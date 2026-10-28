/* rgp:protos */
#define RGP_SELF_MinimapGetFadeMode_329dd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s8 at +0x11B. */

typedef struct Obj_FUN_00329dd0 {
    u8 pad000[0x11B];
    s8 field;         /* +0x11B */
} Obj_FUN_00329dd0;

s8 MinimapGetFadeMode_329dd0(Obj_FUN_00329dd0 *o)
{
    return o->field;
}
