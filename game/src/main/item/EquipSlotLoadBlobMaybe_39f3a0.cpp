/* rgp:protos */
#line 1
#include "types.h"

extern "C" {
extern void *memcpy(void *, const void *, u32);
extern u8 *D_0048374C;
}

class Mgr {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 lookup(s16 a0) { return VCM(s32, (void *, s16), 0x70, a0); }
};

class Buf {
public:
    VC_VPTR_MEMBER; s32 offset() { return VCM0(s32, 0x8); }
    
    s32 capacity(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, int, int, int), 0x10, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
};

typedef struct {
    void *vt;
    s32 unk4;
    s16 unk8;
    s16 unkA;
} BufData;

extern "C" s32 EquipSlotLoadBlobMaybe_39f3a0(Buf *arg0, u8 *arg1, s32 arg2, int rgp_a3)
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
    k = d->unk8;
    if (k > 0) {
        d->unk4 = (*(Mgr **)(*(u8 **)(D_0048374C + 0x44) + 8))->lookup(k);
    } else {
        d->unkA = -1;
        d->unk8 = -1;
        d->unk4 = 0;
    }
    return n;
}
