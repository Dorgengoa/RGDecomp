#include "types.h"

struct QFUN_002544b0 { s32 f0; u8 pad004[0x58]; s32 fend; };
struct AFUN_002544b0 { struct QFUN_002544b0 *f0; s32 f4; };

struct QFUN_002544b0 *EventCameraNodeFindFree_2544b0(struct AFUN_002544b0 *a)
{
    struct QFUN_002544b0 *p;
    s32 i;
    s32 n;

    p = a->f0;
    n = a->f4;
    i = 0;
    while (i < n) {
        if (p->f0 == 0) {
            p->fend = 0;
            return p;
        }
        i++;
        p++;
    }
    return 0;
}
