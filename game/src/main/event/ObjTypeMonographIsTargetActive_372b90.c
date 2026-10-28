/* rgp:protos */
#define RGP_SELF_ObjTypeMonographIsTargetActive_372b90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Obj_func_00372B90 {
    u8 pad000[0xD0];
    s32 mD0;
} Obj_func_00372B90;

s32 ObjTypeMonographIsTargetActive_372b90(Obj_func_00372B90 *o)
{
    return (((o->mD0 & 0x80000000) != 0) ^ 1);
}
