/* rgp:protos */
#define RGP_SELF_FuncDataTableInit_18fc00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Zero the s32 at +0x4. */

typedef struct Obj_FUN_0018fc00 {
    u8 pad000[0x4];
    s32 field;         /* +0x4 */
} Obj_FUN_0018fc00;

void FuncDataTableInit_18fc00(Obj_FUN_0018fc00 *o)
{
    o->field = 0;
}
