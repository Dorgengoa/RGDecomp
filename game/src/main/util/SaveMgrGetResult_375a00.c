/* rgp:protos */
#define RGP_SELF_SaveMgrGetResult_375a00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Address of the sub-object at +0x4F0. */

typedef struct Obj_FUN_00375a00 {
    u8 pad000[0x4F0];
    u8 sub[1];         /* +0x4F0 */
} Obj_FUN_00375a00;

void *SaveMgrGetResult_375a00(Obj_FUN_00375a00 *o)
{
    return o->sub;
}
