#include "types.h"

typedef struct O {
    u8  pad000[0x4AE];
    s16 m4AE;
} O;

s16 CharaBattleHitsTakenIncMaybe_3b00d0(O *o)
{
    return ++o->m4AE;
}
