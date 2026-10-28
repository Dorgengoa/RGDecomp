/* rgp:protos */
#define RGP_SELF_CharaNormalTableGetArray_225820 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x28. */

typedef struct Obj_FUN_00225820 {
    u8 pad000[0x28];
    s32 field;         /* +0x28 */
} Obj_FUN_00225820;

s32 CharaNormalTableGetArray_225820(Obj_FUN_00225820 *o)
{
    return o->field;
}
