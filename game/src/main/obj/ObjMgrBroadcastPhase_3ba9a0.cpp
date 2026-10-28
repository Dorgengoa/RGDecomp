#include "types.h"

class V {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void fC8(s32 a0) { VCM(void, (void *, s32), 0xC8, a0); }
};

extern "C" V *PoolGetUsedElem_36acb0(s32 arg0, s32 arg1);
extern "C" void ObjMgrGroupLetterSlotsReset_3bc270(void *arg0);
extern "C" s32 D_004659C8[4];

extern "C" s32 ObjMgrBroadcastPhase_3ba9a0(u8 *arg0, s32 arg1)
{
    s32 n;
    s32 i;
    V *v;
    u8 *t;

    t = *(u8 **)(arg0 + 4);
    if (t == 0) {
        return 0;
    }
    if (!(*(*(u8 **)(t + 0x20) + 0x24C) & 1)) {
        return 0;
    }
    if (*(s32 *)(arg0 + 0x10) == 0) {
        return 0;
    }
    n = D_004659C8[0];
    for (i = 0; i < n; i++) {
        v = PoolGetUsedElem_36acb0(*(s32 *)(arg0 + 0x10), i);
        if (v != 0) {
            v->fC8(arg1);
        }
    }
    ObjMgrGroupLetterSlotsReset_3bc270(arg0);
    return 1;
}
