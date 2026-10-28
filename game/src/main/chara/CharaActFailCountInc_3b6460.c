/* rgp:protos */
#define RGP_SELF_CharaActFailCountInc_3b6460 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct O {
    u8  pad000[0x1D8];
    s16 m1D8;
} O;

s16 CharaActFailCountInc_3b6460(O *o)
{
    return ++o->m1D8;
}
