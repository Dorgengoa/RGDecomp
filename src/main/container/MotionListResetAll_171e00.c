#include "types.h"

struct N171E00 { struct N171E00 *f00; };
struct T171E00 { u8 pad000[0x4]; struct N171E00 *f04; };

extern void MotionPlayerReset_173870(void *e);

void MotionListResetAll_171e00(struct T171E00 *p)
{
    struct N171E00 *n;
    void *e;

    n = p->f04;
    while (n != 0) {
        e = (u8 *)n + 0x10;
        if (e != 0) {
            MotionPlayerReset_173870(e);
        }
        n = n->f00;
    }
}
