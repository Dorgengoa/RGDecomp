/* rgp:protos */
#define RGP_SELF_IsPcCharaId_1f52d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
u8 IsPcCharaId_1f52d0(s32 a)
{
    s32 t;

    t = a - 0x2AF9;
    return !(t < 0) && t < 0xC;
}
