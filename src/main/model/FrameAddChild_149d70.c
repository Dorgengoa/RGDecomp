#include "types.h"

struct Obj1;

struct Obj0 {
    u8  pad000[8];
    struct Obj1 *m08;
};

struct Obj1 {
    u8  pad000[4];
    struct Obj0 *m04;
};

extern void FrameAppendSibling_149dc0(struct Obj1 *);

void FrameAddChild_149d70(struct Obj0 *p0, struct Obj1 *p1)
{
    if (p1 != 0) {
        if (p0->m08 != 0) {
            FrameAppendSibling_149dc0(p0->m08);
        } else {
            p0->m08 = p1;
        }
        p1->m04 = p0;
    }
}
