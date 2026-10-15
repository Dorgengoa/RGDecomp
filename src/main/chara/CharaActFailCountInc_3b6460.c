#include "types.h"

typedef struct O {
    u8  pad000[0x1D8];
    s16 m1D8;
} O;

s16 CharaActFailCountInc_3b6460(O *o)
{
    return ++o->m1D8;
}
