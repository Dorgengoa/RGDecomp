/* rgp:protos */
#define RGP_SELF_MapDataSetLinkKeyMaybe_1e7b40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s16 at +0x26. */

typedef struct Obj_FUN_001e7b40 {
    u8 pad000[0x26];
    s16 field;         /* +0x26 */
} Obj_FUN_001e7b40;

void MapDataSetLinkKeyMaybe_1e7b40(Obj_FUN_001e7b40 *o, s16 value)
{
    o->field = value;
}
