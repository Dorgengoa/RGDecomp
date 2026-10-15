#include "types.h"

extern "C" {
extern void *memcpy(void *, const void *, u32);
extern u8 *D_004838EC;
}

class Mgr {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual s32 lookup(s16);
};

class Buf {
public:
    virtual s32 offset();
    virtual void v1();
    virtual s32 capacity();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();

};

typedef struct {
    void *vt;
    s32 unk4;
    s16 unk8;
    s16 unkA;
    s16 id;
    s16 pad;
    s32 ref;
} BufData;

extern "C" s32 InvObjLoadState_3d3940(Buf *arg0, u8 *arg1, s32 arg2)
{
    s32 n;
    s32 k;
    BufData *d = (BufData *)arg0;
    s32 c;

    if (arg1 == 0 || arg2 <= 0) {
        return 0;
    }
    n = arg0->capacity();
    if (arg2 < n) {
        n = arg2;
    }
    memcpy((u8 *)arg0 + arg0->offset(), arg1, n);
    d->ref = (*(Mgr **)(*(u8 **)(D_004838EC + 0x40) + 8))->lookup(d->id);
    arg0->v8();
    return n;
}
