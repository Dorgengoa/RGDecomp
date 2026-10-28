/* rgp:protos */
#define RGP_SELF_SortedNodeGetData_21ff00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Address of the sub-object at +0x10. */

typedef struct Obj_FUN_0021ff00 {
    u8 pad000[0x10];
    u8 sub[1];         /* +0x10 */
} Obj_FUN_0021ff00;

void *SortedNodeGetData_21ff00(Obj_FUN_0021ff00 *o)
{
    return o->sub;
}
