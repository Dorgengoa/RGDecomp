/* rgp:protos */
#define RGP_SELF_NumPutUnsigned_1a4290 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct C4290 {
    u8 pad00[0x38];
    u16 m38;
} C4290;

/*rgp*/
/*rgp*/
/*rgp*/

void NumPutUnsigned_1a4290(void *a, s32 b, C4290 *c, s32 d, s32 e)
{
    volatile s32 t;
    u16 f;

    t = b;
    f = c->m38 & 0x4A;
    switch (f) {
    case 0x40:
        NumPutOct_1a4560(a, b, c, d, e);
        break;
    case 8:
        NumPutHex_1a4370(a, b, c, d, e);
        break;
    default:
        NumPutU64_1a44f0(a, b, c, d, e);
        break;
    }
}
