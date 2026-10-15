#include "types.h"

typedef struct O {
    u8  pad000[0xE0A];
    s16 mE0A;
} O;

s16 VariantPoolScopeEnter_3da020(O *o)
{
    return ++o->mE0A;
}
