/* rgp:protos */
#define RGP_SELF_MapLinkSetTopY_1e9200 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the f32 at +0x10. */

typedef struct Obj_FUN_001e9200 {
    u8 pad000[0x10];
    f32 field;         /* +0x10 */
} Obj_FUN_001e9200;

void MapLinkSetTopY_1e9200(Obj_FUN_001e9200 *o, f32 value)
{
    o->field = value;
}
