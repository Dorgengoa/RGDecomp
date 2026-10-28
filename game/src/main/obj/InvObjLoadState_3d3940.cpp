/* rgp:protos */
#line 1
#include "types.h"

extern "C" {
extern void *memcpy(void *, const void *, u32);
extern u8 *D_004838EC;
}

class Mgr {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    void v8() { VCM0(void, 0x28); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 lookup(s16 a0) { return VCM(s32, (void *, s16), 0x70, a0); }
};

class Buf {
public:
    VC_VPTR_MEMBER; s32 offset() { return VCM0(s32, 0x8); }
    
    s32 capacity(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, int, int, int), 0x10, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
    
    
    
    
    
    void v8() { VCM0(void, 0x28); }

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

extern "C" s32 InvObjLoadState_3d3940(Buf *arg0, u8 *arg1, s32 arg2, int rgp_a3)
{
    s32 n;
    s32 k;
    BufData *d = (BufData *)arg0;
    s32 c;

    if (arg1 == 0 || arg2 <= 0) {
        return 0;
    }
    n = arg0->capacity((int)(long)(arg1), (int)(long)(arg2), (int)(long)(rgp_a3));
    if (arg2 < n) {
        n = arg2;
    }
    memcpy((u8 *)arg0 + arg0->offset(), arg1, n);
    d->ref = (*(Mgr **)(*(u8 **)(D_004838EC + 0x40) + 8))->lookup(d->id);
    arg0->v8();
    return n;
}
