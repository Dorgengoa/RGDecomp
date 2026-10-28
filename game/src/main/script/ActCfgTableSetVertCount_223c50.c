/* rgp:protos */
#define RGP_SELF_ActCfgTableSetVertCount_223c50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s16 at +0x66. */

typedef struct Obj_FUN_00223c50 {
    u8 pad000[0x66];
    s16 field;         /* +0x66 */
} Obj_FUN_00223c50;

void ActCfgTableSetVertCount_223c50(Obj_FUN_00223c50 *o, s16 value)
{
    o->field = value;
}
