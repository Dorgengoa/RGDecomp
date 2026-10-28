/* rgp:protos */
#define RGP_SELF_EntryListSetChildCount_3237a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the u8 at +0x32. */

typedef struct Obj_FUN_003237a0 {
    u8 pad000[0x32];
    u8 field;         /* +0x32 */
} Obj_FUN_003237a0;

void EntryListSetChildCount_3237a0(Obj_FUN_003237a0 *o, u8 value)
{
    o->field = value;
}
