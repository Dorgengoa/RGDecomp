/* rgp:protos */
#line 1
#include "types.h"

class Obj {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    bool v7(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return (vc_u8)VCM(vc_u32, (void *, int, int, int), 0x24, rgp_fwd1, rgp_fwd2, rgp_fwd3) != 0; }
    
    
    void v10() { VCM0(void, 0x30); }
};

struct ObjRaw {
    u8 pad000[0x10];
    s32 m10;
    u8 pad014[0x4];
    s32 m18;
};

extern "C" s32 D_00465B00 __attribute__((section(".data")));
extern "C" s32 D_00465B08 __attribute__((section(".data")));
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
        ok = o->v7((int)(long)(b), (int)(long)(c), (int)(long)(d));
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
