#include "types.h"

typedef struct C4290 {
    u8 pad00[0x38];
    u16 m38;
} C4290;

extern void NumPutHex_1a4370(void *a, s32 b, C4290 *c, s32 d, s32 e, s32 f);
extern void NumPutOct_1a4560(void *a, s32 b, C4290 *c, s32 d, s32 e, s32 f);
extern void NumPutU64_1a44f0(void *a, s32 b, C4290 *c, s32 d, s32 e, s32 f);

void NumPutUnsigned_1a4290(void *a, s32 b, C4290 *c, s32 d, s32 e)
{
    volatile s32 t;
    u16 f;

    t = b;
    f = c->m38 & 0x4A;
    switch (f) {
    case 0x40:
        NumPutOct_1a4560(a, b, c, d, e, 0);
        break;
    case 8:
        NumPutHex_1a4370(a, b, c, d, e, 0);
        break;
    default:
        NumPutU64_1a44f0(a, b, c, d, e, 0);
        break;
    }
}
