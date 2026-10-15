#include "types.h"

struct B00370170 {
    virtual s16 v0();
};
struct O00370170 : B00370170 {};
struct T00370170 { struct O00370170 *f00; s16 f04; s16 f06; };

extern "C" struct T00370170 *IterInit_370170(struct T00370170 *p, struct O00370170 *a)
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
    return p;
}
