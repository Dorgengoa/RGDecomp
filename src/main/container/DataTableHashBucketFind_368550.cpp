#include "types.h"

class C368550 {
public:
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual s32 *f40();
    virtual void w00();
    virtual void w01();
    virtual void w02();
    virtual void w03();
    virtual s32 f54(s32);
};

struct Bits7A {
    u8 b0 : 1;
    u8 b1 : 1;
    u8 b2 : 1;
    u8 rest : 5;
};

extern "C" s32 *DataTableHashBucketFind_368550(C368550 *arg0, u16 arg1, s32 *arg2)
{
    s32 *p;
    s32 v;
    bool ok;

    if (!((Bits7A *)((u8 *)arg0 + 0x7A))->b2) {
        return 0;
    }
    *arg2 = *(u16 *)((u8 *)arg0 + 0x82) - arg1;
    p = arg0->f40() + arg1;
    while ((bool)*p && *arg2 > 0) {
        v = arg0->f54(*p) & 0xFFFF;
        if (arg1 == v) {
            return p;
        }
        if (arg1 < v) {
            break;
        }
        p++;
        (*arg2)--;
    }
    return 0;
}
