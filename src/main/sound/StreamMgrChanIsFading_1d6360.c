#include "types.h"

typedef struct E_001d6360 {
    u8 pad000[0xE0];
} E_001d6360;

extern s32 StreamChanIsFading_1d6f60(E_001d6360 *e);

s32 StreamMgrChanIsFading_1d6360(E_001d6360 *a, s32 n)
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
    return StreamChanIsFading_1d6f60(&a[n]);
}
