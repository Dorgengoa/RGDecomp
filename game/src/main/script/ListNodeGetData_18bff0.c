/* rgp:protos */
#define RGP_SELF_ListNodeGetData_18bff0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s32 at +0x10. */

typedef struct Obj_FUN_0018bff0 {
    u8 pad000[0x10];
    s32 field;         /* +0x10 */
} Obj_FUN_0018bff0;

s32 ListNodeGetData_18bff0(Obj_FUN_0018bff0 *o)
{
    return o->field;
}
