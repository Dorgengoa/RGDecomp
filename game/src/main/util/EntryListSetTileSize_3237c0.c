/* rgp:protos */
#define RGP_SELF_EntryListSetTileSize_3237c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s16 at +0x14. */

typedef struct Obj_FUN_003237c0 {
    u8 pad000[0x14];
    s16 field;         /* +0x14 */
} Obj_FUN_003237c0;

void EntryListSetTileSize_3237c0(Obj_FUN_003237c0 *o, s16 value)
{
    o->field = value;
}
