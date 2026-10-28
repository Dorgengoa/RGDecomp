/* rgp:protos */
#define RGP_SELF_MesWinIsActive_2774d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s8 at +0x1C48. */

typedef struct Obj_FUN_002774d0 {
    u8 pad000[0x1C48];
    s8 field;         /* +0x1C48 */
} Obj_FUN_002774d0;

s8 MesWinIsActive_2774d0(Obj_FUN_002774d0 *o)
{
    return o->field;
}
