/* rgp:protos */
#define RGP_SELF_EntrySetScale_323c10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the f32 at +0x4. */

typedef struct Obj_FUN_00323c10 {
    u8 pad000[0x4];
    f32 field;         /* +0x4 */
} Obj_FUN_00323c10;

void EntrySetScale_323c10(Obj_FUN_00323c10 *o, f32 value)
{
    o->field = value;
}
