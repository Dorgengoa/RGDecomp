/* rgp:protos */
#define RGP_SELF_EntryGetScale_323b30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the f32 at +0x4. */

typedef struct Obj_FUN_00323b30 {
    u8 pad000[0x4];
    f32 field;         /* +0x4 */
} Obj_FUN_00323b30;

f32 EntryGetScale_323b30(Obj_FUN_00323b30 *o)
{
    return o->field;
}
