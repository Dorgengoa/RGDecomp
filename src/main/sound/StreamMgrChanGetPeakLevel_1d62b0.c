#include "types.h"

typedef struct E_001d62b0 {
    u8 pad000[0xE0];
} E_001d62b0;

extern s32 StreamChanGetPeakLevel_1d6a00(E_001d62b0 *e);

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
