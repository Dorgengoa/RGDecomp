/* rgp:protos */
#line 1
#include "types.h"
#pragma optimization_level 3
#pragma opt_common_subs off
class VC_4061f0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f(s16 a0) { return VCM(s32, (void *, s16), 0x70, a0); }
};

extern "C" {

extern void *IterNext_370040(void *arg0);
extern void IterInit_370170(void *, s32, int, int);

s32 WorldSubsysLinkIds_4061f0(s32 arg0, void *arg1, int rgp_a2, int rgp_a3)
{
    u8 sp58[0x8];
    u8 *e;
    u8 *p;
    s32 n;
    s32 i;
    s32 a;

    if (arg1 == NULL) {
        return 0;
    }
    a = arg0;
    if (arg0 != 0) {
        a += 0x88;
    }
    IterInit_370170(sp58, a, (int)rgp_a2, (int)rgp_a3);
    while ((e = (u8 *)IterNext_370040(sp58)) != NULL) {
        *(s32 *)(e + 4) = (*(VC_4061f0 **)(*(u8 **)((u8 *)arg1 + 0x40) + 8))->f(*(s32 *)(e + 4));
        p = *(u8 **)(e + 0xC);
        n = *(s16 *)(e + 8);
        if (p != NULL && n > 0) {
            for (i = 0; i < n; i++) {
                *(s32 *)p = (*(VC_4061f0 **)(*(u8 **)((u8 *)arg1 + 0x40) + 8))->f(*(s32 *)p);
                p += 0x10;
            }
        }
    }
    return 1;
}

}
