#include "types.h"
extern "C" {

extern s32 ObjRecCollectLiveObjects_1c5150(void *, void *, s32);

class VC_0 {
public:
    u8 pad[0x68];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f(s32 x0, s32 x1, s32 x2) { return VCM(s32, (void *, s32, s32, s32), 0x60, x0, x1, x2); }
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
