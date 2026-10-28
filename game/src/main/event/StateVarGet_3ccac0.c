/* rgp:protos */
#define RGP_SELF_StateVarGet_3ccac0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct Obj {
    u8 pad000[0x128];
    s16 arr[0x80];
};

s16 StateVarGet_3ccac0(struct Obj *o, s32 i)
{
    if (i < 0 || i >= 0x80) {
        return -1;
    }
    return o->arr[i];
}
