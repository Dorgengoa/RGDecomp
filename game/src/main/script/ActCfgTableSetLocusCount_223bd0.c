/* rgp:protos */
#define RGP_SELF_ActCfgTableSetLocusCount_223bd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s16 at +0x76. */

typedef struct Obj_FUN_00223bd0 {
    u8 pad000[0x76];
    s16 field;         /* +0x76 */
} Obj_FUN_00223bd0;

void ActCfgTableSetLocusCount_223bd0(Obj_FUN_00223bd0 *o, s16 value)
{
    o->field = value;
}
