/* rgp:protos */
#define RGP_SELF_StreamMgrChanGetPeakLevel_1d62b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct E_001d62b0 {
    u8 pad000[0xE0];
} E_001d62b0;

/*rgp*/

s32 StreamMgrChanGetPeakLevel_1d62b0(E_001d62b0 *a, s32 n)
{
    if (n < 0) {
        goto bad;
    }
    if (n < 4) {
        goto body;
    }
bad:
    return 0;
body:
    return StreamChanGetPeakLevel_1d6a00(&a[n]);
}
