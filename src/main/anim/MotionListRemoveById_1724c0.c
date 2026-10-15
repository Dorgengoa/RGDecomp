#include "types.h"

struct N1724C0 { struct N1724C0 *f00; };
struct T1724C0 { u8 pad000[0x4]; struct N1724C0 *f04; };

extern s32 MotionPlayerRemoveById_172700(void *e, void *a);

s32 MotionListRemoveById_1724c0(struct T1724C0 *p, void *a)
{
    struct N1724C0 *n;
    void *e;
    s32 sum;

    n = p->f04;
    sum = 0;
    while (n != 0) {
        e = (u8 *)n + 0x10;
        if (e != 0) {
            sum += MotionPlayerRemoveById_172700(e, a);
        }
        n = n->f00;
    }
    return sum;
}
