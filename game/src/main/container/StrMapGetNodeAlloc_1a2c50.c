/* rgp:protos */
#define RGP_SELF_StrMapGetNodeAlloc_1a2c50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Address of the sub-object at +0x4. */

typedef struct Obj_FUN_001a2c50 {
    u8 pad000[0x4];
    u8 sub[1];         /* +0x4 */
} Obj_FUN_001a2c50;

void *StrMapGetNodeAlloc_1a2c50(Obj_FUN_001a2c50 *o)
{
    return o->sub;
}
