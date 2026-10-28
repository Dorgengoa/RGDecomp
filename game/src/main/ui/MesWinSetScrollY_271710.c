/* rgp:protos */
#define RGP_SELF_MesWinSetScrollY_271710 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s32 at +0x192C. */

typedef struct Obj_FUN_00271710 {
    u8 pad000[0x192C];
    s32 field;         /* +0x192C */
} Obj_FUN_00271710;

void MesWinSetScrollY_271710(Obj_FUN_00271710 *o, s32 value)
{
    o->field = value;
}
