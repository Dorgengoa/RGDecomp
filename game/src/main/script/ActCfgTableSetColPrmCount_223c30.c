/* rgp:protos */
#define RGP_SELF_ActCfgTableSetColPrmCount_223c30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s16 at +0x6A. */

typedef struct Obj_FUN_00223c30 {
    u8 pad000[0x6A];
    s16 field;         /* +0x6A */
} Obj_FUN_00223c30;

void ActCfgTableSetColPrmCount_223c30(Obj_FUN_00223c30 *o, s16 value)
{
    o->field = value;
}
