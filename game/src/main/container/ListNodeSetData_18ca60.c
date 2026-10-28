/* rgp:protos */
#define RGP_SELF_ListNodeSetData_18ca60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s32 at +0x10. */

typedef struct Obj_FUN_0018ca60 {
    u8 pad000[0x10];
    s32 field;         /* +0x10 */
} Obj_FUN_0018ca60;

void ListNodeSetData_18ca60(Obj_FUN_0018ca60 *o, s32 value)
{
    o->field = value;
}
