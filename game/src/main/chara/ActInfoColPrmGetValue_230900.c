/* rgp:protos */
#define RGP_SELF_ActInfoColPrmGetValue_230900 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x4. */

typedef struct Obj_FUN_00230900 {
    u8 pad000[0x4];
    s32 field;         /* +0x4 */
} Obj_FUN_00230900;

s32 ActInfoColPrmGetValue_230900(Obj_FUN_00230900 *o)
{
    return o->field;
}
