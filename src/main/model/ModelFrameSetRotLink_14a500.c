#include "types.h"
typedef struct T0014a500 {
    u8 pad[0xC];
    s32 fC;
} T0014a500;

typedef struct S0014a500 {
    u8 pad00[0x18];
    T0014a500 *f18;
    u8 pad1C[0x29 - 0x1C];
    u8 b29;
    u8 pad2A[1];
    u8 b2B;
} S0014a500;

void ModelFrameSetRotLink_14a500(S0014a500 *s, T0014a500 *b)
{
    s32 *p;

    s->f18 = b;
    if (b != 0) {
        p = &b->fC;
        if (b->fC == 0) {
            *p = 1;
        }
    }
    s->b2B = 1;
    s->b29 = 1;
}
