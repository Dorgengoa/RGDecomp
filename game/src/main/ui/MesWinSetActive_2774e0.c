/* rgp:protos */
#define RGP_SELF_MesWinSetActive_2774e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the u8 at +0x1C48. */

typedef struct Obj_FUN_002774e0 {
    u8 pad000[0x1C48];
    u8 field;         /* +0x1C48 */
} Obj_FUN_002774e0;

void MesWinSetActive_2774e0(Obj_FUN_002774e0 *o, u8 value)
{
    o->field = value;
}
