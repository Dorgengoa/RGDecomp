#include "types.h"

class Obj {
public:
    virtual s32 v0();
    virtual s32 v1();
    virtual s32 v2();
    virtual s32 v3();
    virtual s32 v4();
    virtual s32 v5();
    virtual s32 v6();
    virtual bool v7();
    virtual s32 v8();
    virtual s32 v9();
    virtual void v10();
};

struct ObjRaw {
    u8 pad000[0x10];
    s32 m10;
    u8 pad014[0x4];
    s32 m18;
};

extern const s32 D_00465B00 __attribute__((section(".data")));
extern const s32 D_00465B08 __attribute__((section(".data")));
extern "C" void ItemSetup_3d4ff0(class Obj *o, void *b, s32 c, void *d);

extern "C" s32 ItemGameRecSetup_3d0d80(class Obj *o, void *b, s32 c, void *d)
{
    bool ok;

    ok = D_00465B00 <= c;
    ((struct ObjRaw *)o)->m18 = 0;
    if (ok) {
        ok = c <= D_00465B08;
    }
    if (!ok) {
        ok = o->v7();
        if (!ok) {
            return 0;
        }
    }
    ItemSetup_3d4ff0(o, b, c, d);
    if (((struct ObjRaw *)o)->m10 == 0) {
        o->v10();
        return 0;
    }
    return 1;
}
