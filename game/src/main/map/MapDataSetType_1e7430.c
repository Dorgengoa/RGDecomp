/* rgp:protos */
#define RGP_SELF_MapDataSetType_1e7430 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the u8 at +0x21. */

typedef struct Obj_FUN_001e7430 {
    u8 pad000[0x21];
    u8 field;         /* +0x21 */
} Obj_FUN_001e7430;

void MapDataSetType_1e7430(Obj_FUN_001e7430 *o, u8 value)
{
    o->field = value;
}
