#include "types.h"

struct B36FFF0 {
    virtual void v0();
    virtual s32 v1(s16 i);
};
struct O36FFF0 : B36FFF0 {};
struct T36FFF0 { struct O36FFF0 *f00; s16 f04; s16 f06; };

extern "C" s32 IterSeek_36fff0(struct T36FFF0 *p, s32 i)
{
    if (i >= 0) {
        if (i < p->f04) {
            p->f06 = (s16)i;
            return p->f00->v1((s16)i);
        }
        return 0;
    }
    return 0;
}
