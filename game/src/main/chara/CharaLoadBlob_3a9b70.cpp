#pragma optimization_level 3
#pragma opt_common_subs off
#include "types.h"

extern "C" {
extern void *memcpy(void *, const void *, u32);
extern u8 *D_0048381C;
}

class Mgr {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 lookup(s16 a0) { return VCM(s32, (void *, s16), 0x70, a0); }
};

class Buf {
public:
    VC_VPTR_MEMBER; s32 offset() { return VCM0(s32, 0x8); }
    
    s32 capacity() { return VCM0(s32, 0x10); }
    
    
    
    
    
    

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

extern "C" s32 CharaLoadBlob_3a9b70(Buf *arg0, u8 *arg1, s32 arg2)
{
    u8 backup[0x190] __attribute__((aligned(16)));
    s32 n;
    s32 k;
    BufData *d = (BufData *)arg0;
    s32 c;

    if (arg1 == 0 || arg2 <= 0) {
        return 0;
    }
    memcpy(backup,(u8 *)arg0+0x308,0x190);
    n = arg0->capacity();
    if (arg2 < n) {
        n = arg2;
    }
    memcpy((u8 *)arg0 + arg0->offset(), arg1, n);
    memcpy((u8 *)arg0+0x308,backup,0x190);
    *(s32 *)((u8 *)arg0+0x230) = (*(Mgr **)(*(u8 **)(D_0048381C + 0x60) + 0xC))->lookup(*(s16 *)((u8 *)arg0+4));

    return n;
}
