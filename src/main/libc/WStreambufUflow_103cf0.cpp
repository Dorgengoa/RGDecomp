#include "types.h"

struct C103820 {
    virtual s32 v0();
    virtual s32 v1();
    virtual s32 v2();
    virtual s32 v3();
    virtual s32 v4();
    virtual s32 v5();
    virtual s32 v6();
    virtual s32 v7();
    s32 pad04;
    u8 *m08;
};

extern "C" s32 WStreambufUflow_103cf0(struct C103820 *p)
{
    u8 *q;
    s32 r;

    if (p->v7() == -1) {
        r = -1;
    } else {
        q = p->m08;
        p->m08 = q + 4;
        r = *(u16 *)q;
    }
    return r;
}
