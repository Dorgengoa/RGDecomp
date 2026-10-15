#include "types.h"
extern "C" {

extern s32 ObjRecCollectLiveObjects_1c5150(void *, void *, s32);

class VC_0 {
public:
    u8 pad[0x68];
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual void d21();
    virtual s32 f(s32 x0, s32 x1, s32 x2);
};

s32 SceneMapAreasCollectCollTrisMaybe_1c5090(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 total;
    s32 i;
    s32 n;
    s32 r;
    void *buf[0x14];

    n = ObjRecCollectLiveObjects_1c5150(arg0, buf, 0x14);
    total = 0;
    for (i = 0; i < n; i++) {
        r = ((VC_0 *)buf[i])->f(arg1, arg2, arg3);
        arg1 += r * 0x60;
        total += r;
        arg3 -= r;
        if (arg3 < 0) {
            break;
        }
    }
    return total;
}

}
