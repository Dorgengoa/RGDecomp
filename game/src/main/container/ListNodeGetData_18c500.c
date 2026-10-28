/* rgp:protos */
#define RGP_SELF_ListNodeGetData_18c500 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x10. */

typedef struct Obj_FUN_0018c500 {
    u8 pad000[0x10];
    s32 field;         /* +0x10 */
} Obj_FUN_0018c500;

s32 ListNodeGetData_18c500(Obj_FUN_0018c500 *o)
{
    return o->field;
}
