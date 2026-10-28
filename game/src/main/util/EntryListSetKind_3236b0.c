/* rgp:protos */
#define RGP_SELF_EntryListSetKind_3236b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s16 at +0x16. */

typedef struct Obj_FUN_003236b0 {
    u8 pad000[0x16];
    s16 field;         /* +0x16 */
} Obj_FUN_003236b0;

void EntryListSetKind_3236b0(Obj_FUN_003236b0 *o, s16 value)
{
    o->field = value;
}
