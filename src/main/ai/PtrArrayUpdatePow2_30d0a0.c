#include "types.h"
typedef struct S0030d0a0 {
    u8 pad00[0x4];
    u32 f4;
    u8 pad08[0x4];
    u32 fC;
} S0030d0a0;

void PtrArrayUpdatePow2_30d0a0(S0030d0a0 *s)
{
    s->fC = 1;
    while (s->fC < s->f4) {
        s->fC <<= 1;
    }
}
