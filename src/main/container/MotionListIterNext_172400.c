#include "types.h"
typedef struct N00172400 {
    struct N00172400 *next;   /* +0x0 */
    u8 pad04[0x8];
    s32 fC;                   /* +0xC */
    u8 data[0x10];            /* +0x10 */
} N00172400;

typedef struct S00172400 {
    u8 pad[0x8];
    N00172400 *f8;
} S00172400;

void *MotionListIterNext_172400(S00172400 *s, s32 *out)
{
    N00172400 *p;
    void *r;

    p = s->f8;
    if (p == 0) {
        r = 0;
    } else {
        r = p->data;
        *out = p->fC;
        s->f8 = s->f8->next;
    }
    return r;
}
