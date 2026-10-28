/* rgp:protos */
#define RGP_SELF_MesWinGetArrowSnap_271720 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s8 at +0x1C38. */

typedef struct Obj_FUN_00271720 {
    u8 pad000[0x1C38];
    s8 field;         /* +0x1C38 */
} Obj_FUN_00271720;

s8 MesWinGetArrowSnap_271720(Obj_FUN_00271720 *o)
{
    return o->field;
}
