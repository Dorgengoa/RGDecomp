#include "types.h"
struct S3BA320 { u8 pad[0x10]; s32 unk10; };
extern "C" {
class VC {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f() { return VCM0(s32, 0x434); }
};
extern VC *PoolGetUsedElem_36acb0(s32, s32);
extern s32 D_004659C8[4];

VC *ObjMgrGetNthLive_3ba320(S3BA320 *arg0, s32 arg1)
{
    s32 n;
    s32 lim;
    s32 i;
    VC *p;

    if (arg0->unk10 == 0) {
        return 0;
    }
    n = 0;
    lim = D_004659C8[0];
    for (i = 0; i < lim; i++) {
        p = PoolGetUsedElem_36acb0(arg0->unk10, i);
        if (p != 0 && p->f() == 0) {
            if (n == arg1) {
                return p;
            }
            n += 1;
        }
    }
    return 0;
}
}
