/* rgp:protos */
#define RGP_SELF_PartyGetReserveId_3c1d90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct Obj {
    u8 pad000[0x196];
    s16 arr[0x7];
};

s16 PartyGetReserveId_3c1d90(struct Obj *o, s32 i)
{
    if (i < 0 || i >= 0x7) {
        return -1;
    }
    return o->arr[i];
}
