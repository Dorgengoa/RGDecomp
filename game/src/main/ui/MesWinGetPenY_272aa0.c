/* rgp:protos */
#define RGP_SELF_MesWinGetPenY_272aa0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x1938. */

typedef struct Obj_FUN_00272aa0 {
    u8 pad000[0x1938];
    s32 field;         /* +0x1938 */
} Obj_FUN_00272aa0;

s32 MesWinGetPenY_272aa0(Obj_FUN_00272aa0 *o)
{
    return o->field;
}
