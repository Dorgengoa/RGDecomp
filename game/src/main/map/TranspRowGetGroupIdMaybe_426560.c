/* rgp:protos */
#define RGP_SELF_TranspRowGetGroupIdMaybe_426560 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Sub_func_00426560 {
    s16 val;
} Sub_func_00426560;

typedef struct Obj_func_00426560 {
    u8 pad000[0x10];
    Sub_func_00426560 *p;
} Obj_func_00426560;

s32 TranspRowGetGroupIdMaybe_426560(Obj_func_00426560 *o)
{
    Sub_func_00426560 *p;

    p = o->p;
    if (p != 0) {
        return p->val;
    }
    return -1;
}
