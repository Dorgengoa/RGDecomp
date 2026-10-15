#include "types.h"

struct B00370100 {
    virtual s16 v0();
};
struct O00370100 : B00370100 {};
struct T00370100 { struct O00370100 *f00; s16 f04; s16 f06; };

extern "C" void IterAttach_370100(struct T00370100 *p, struct O00370100 *a)
{
    if (a != 0) {
        p->f00 = a;
    }
    p->f04 = 0;
    if (p->f00 != 0) {
        p->f04 = p->f00->v0();
    }
    p->f06 = 0;
    p->f06 = -1;
}
