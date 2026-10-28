/* rgp:protos */
#define RGP_SELF_MesWinSetPenX_272af0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s32 at +0x1934. */

typedef struct Obj_FUN_00272af0 {
    u8 pad000[0x1934];
    s32 field;         /* +0x1934 */
} Obj_FUN_00272af0;

void MesWinSetPenX_272af0(Obj_FUN_00272af0 *o, s32 value)
{
    o->field = value;
}
