#include "types.h"

typedef struct E { u8 b[0x24]; } E;
typedef struct P { u8 pad0[0xA0]; E *fA0; u8 padA[0x4]; u16 fA8; } P;

E *NavGraphGetNode_310cd0(P *p, u32 i)
{
    E *base = p->fA0;
    if (base == 0 || p->fA8 <= i) return 0;
    return &base[i];
}
