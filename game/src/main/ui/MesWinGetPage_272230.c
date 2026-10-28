/* rgp:protos */
#define RGP_SELF_MesWinGetPage_272230 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s16 at +0x58. */

typedef struct Obj_FUN_00272230 {
    u8 pad000[0x58];
    s16 field;         /* +0x58 */
} Obj_FUN_00272230;

s16 MesWinGetPage_272230(Obj_FUN_00272230 *o)
{
    return o->field;
}
