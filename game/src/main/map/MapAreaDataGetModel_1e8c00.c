/* rgp:protos */
#define RGP_SELF_MapAreaDataGetModel_1e8c00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Address of the sub-object at +0x30. */

typedef struct Obj_FUN_001e8c00 {
    u8 pad000[0x30];
    u8 sub[1];         /* +0x30 */
} Obj_FUN_001e8c00;

void *MapAreaDataGetModel_1e8c00(Obj_FUN_001e8c00 *o)
{
    return o->sub;
}
