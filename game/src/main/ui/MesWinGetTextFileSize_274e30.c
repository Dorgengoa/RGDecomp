/* rgp:protos */
#define RGP_SELF_MesWinGetTextFileSize_274e30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x1958. */

typedef struct Obj_FUN_00274e30 {
    u8 pad000[0x1958];
    s32 field;         /* +0x1958 */
} Obj_FUN_00274e30;

s32 MesWinGetTextFileSize_274e30(Obj_FUN_00274e30 *o)
{
    return o->field;
}
