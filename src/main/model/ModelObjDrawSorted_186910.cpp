#include "types.h"

struct Base {
    u8 pad000[0x1B0];
};

class A : public Base {
public:
    virtual s32 v0();
    virtual s32 v1();
    virtual s32 v2();
    virtual s32 v3();
};

extern "C" void *GetDrawCtx_15de80(void);
extern "C" s32 ModelDrawSorted_14f650(class A *a, void *b, void *c);

extern "C" s32 ModelObjDrawSorted_186910(class A *a)
{
    if (a->v3() == 0) {
        return 0;
    }
    return ModelDrawSorted_14f650(a, GetDrawCtx_15de80(), (u8 *)a + 0x120);
}
