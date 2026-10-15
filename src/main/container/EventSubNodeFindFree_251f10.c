#include "types.h"

struct QFUN_00251f10 { s32 f0; u8 pad004[0x48]; s32 fend; };
struct AFUN_00251f10 { struct QFUN_00251f10 *f0; s32 f4; };

struct QFUN_00251f10 *EventSubNodeFindFree_251f10(struct AFUN_00251f10 *a)
{
    struct QFUN_00251f10 *p;
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
