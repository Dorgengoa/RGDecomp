/* rgp:protos */
#define RGP_SELF_NumPutSigned_1a4300 1
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

void NumPutSigned_1a4300(void *a, s32 b, C4290 *c, s32 d, s32 e)
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
        NumPutS64_1a4430(a, b, c, d, (long long)(e));
        break;
    }
}
