#include "types.h"
extern "C" {
extern s32 GroupEntryMatchesKey_3f41b0(s32, s32);
class VC_0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f(s32 a0) { return VCM(s32, (void *, s32), 0x70, a0); }
};

s32 GroupGetRecordById_425590(void *self, s16 arg1)
{
    u8 *node;
    s32 i;
    s32 t;
    s32 r;
    if (*(s32 *)((u8 *)self + 0xC) == 0) {
        return 0;
    }
    node = *(u8 **)((u8 *)self + 0x8);
    for (i = 0; i < 2; i++, node += 0x98) {
        t = *(s32 *)(node + 0x94);
        if ((t != 0) && (GroupEntryMatchesKey_3f41b0(t, -1) != 0)) {
            r = ((VC_0 *)node)->f(arg1);
            if (r != 0) {
                return r;
            }
        }
    }
    return 0;
}
}
