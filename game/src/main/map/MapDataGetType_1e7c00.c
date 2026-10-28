/* rgp:protos */
#define RGP_SELF_MapDataGetType_1e7c00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s8 at +0x21. */

typedef struct Obj_FUN_001e7c00 {
    u8 pad000[0x21];
    s8 field;         /* +0x21 */
} Obj_FUN_001e7c00;

s8 MapDataGetType_1e7c00(Obj_FUN_001e7c00 *o)
{
    return o->field;
}
