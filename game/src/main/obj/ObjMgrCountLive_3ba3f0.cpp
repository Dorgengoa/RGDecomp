#include "types.h"
#pragma opt_common_subs off

class C3ba3f0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f434() { return VCM0(s32, 0x434); }
};

extern "C" {
extern C3ba3f0 *PoolGetUsedElem_36acb0(s32, s32);
extern s32 D_004659C8[4];

s32 ObjMgrCountLive_3ba3f0(void *arg0)
{
    s32 n;
    s32 cnt;
    s32 i;
    C3ba3f0 *o;

    if (*(s32 *)((u8 *)arg0 + 0x10) == 0) {
        return 0;
    }
    n = 0;
    cnt = D_004659C8[0];
    for (i = 0; i < cnt; i++) {
        o = PoolGetUsedElem_36acb0(*(s32 *)((u8 *)arg0 + 0x10), i);
        if (o != NULL && o->f434() == 0) {
            n++;
        }
    }
    return n;
}
}
